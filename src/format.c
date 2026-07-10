/*
 * Copyright (c) 2026, Noel Allen. All rights reserved.
 * SPDX-License-Identifier: MIT
 */

#include <format.h>

#include <attributes.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

__weak FILE _STDIN = {0};
__weak FILE _STDOUT = {1};
__weak FILE _STDERR = {2};


int format_flags(const char *fmt, uint8_t *flags) {
    const char *start = fmt;

    for (;;) {
        switch (*fmt) {
            case '-':
                *flags |= FORMAT_FLAG_MINUS;
                fmt++;
                break;
            case '+':
                *flags |= FORMAT_FLAG_PLUS;
                fmt++;
                break;
            case ' ':
                *flags |= FORMAT_FLAG_SPACE;
                fmt++;
                break;
            case '#':
                *flags |= FORMAT_FLAG_ALT;
                fmt++;
                break;
            case '0':
                *flags |= FORMAT_FLAG_ZERO;
                fmt++;
                break;
            default:
                return (int)(fmt - start);
        }
    }
}

int format_width(const char *fmt, int *pwidth) {
    if (*fmt == '*') {
        *pwidth = -1;
        return 1;
    }

    const char *start = fmt;
    if ((*fmt < '0') || (*fmt > '9')) {
        return 0;
    }

    int width = 0;

    while ((*fmt >= '0') && (*fmt <= '9')) {
        width = width * 10 + (*fmt - '0');
        fmt++;
    }

    *pwidth = width;
    return (int)(fmt - start);
}


int format_size(const char *fmt, FormatSize_t *psize) {
    const char *start = fmt;

    *psize = FORMAT_SIZE_NONE;

    if (*fmt == '\0') {
        return 0;
    }

    switch (*fmt++) {
        case 'h':
            if (*fmt == 'h') {
                fmt++;
                *psize = FORMAT_SIZE_HH;
            } else {
                *psize = FORMAT_SIZE_H;
            }
            break;

        case 'l':
            if (*fmt == 'l') {
                fmt++;
                *psize = FORMAT_SIZE_LL;
            } else {
                *psize = FORMAT_SIZE_L;
            }
            break;

        case 'L':
            *psize = FORMAT_SIZE_L_UPPER;
            break;

        case 'j':
            *psize = FORMAT_SIZE_J;
            break;

        case 'z':
            *psize = FORMAT_SIZE_Z;
            break;

        case 't':
            *psize = FORMAT_SIZE_T;
            break;

        default:
            return 0;
    }

    return (int)(fmt - start);
}


// Parse format: [flags][width][.precision][length]conversion
int format_convertion(const char *fmt, FormatConv_t *out) {
    if ((fmt == NULL) || (out == NULL) || (*fmt == '\0')) {
        return -(int)EINVAL;
    }

    const char *start = fmt;
    memset(out, 0, sizeof(*out));

    // Check for "%%" first
    if (*fmt == '%') {
        out->conversion = '%';
        return 1;
    }
    
    // Get Format Flags
    int ret = format_flags(fmt, &out->flags);
    if (ret < 0) {
        return ret;
    }
    fmt += ret;

    // Get Format Width
    ret = format_width(fmt, &out->width);
    if (ret < 0) {
        return ret;
    } else {
        if (ret > 0) {
            out->width_present = true;
        }
    }
    fmt += ret;

    /* Precision */
    if (*fmt == '.') {
        fmt++;
        out->precision_present = true;
        ret = format_width(fmt, &out->precision);
        if (ret < 0) {
            return ret;
        }
        if (ret == 0) {
            out->precision = 0;
        }
        fmt += ret;
    }

    // Get Size    
    ret = format_size(fmt, &out->size);
    if (ret < 0) {
        return ret;
    }
    fmt += ret;

    char ch = *fmt++;
    switch (ch) {
        case 'X':
        case 'P':
            out->flags |= FORMAT_FLAG_UPPER;
            __fallthrough;
        case 'x':
        case 'p':
            out->base = 16;
            out->conversion = 'd';
            break;

        case 'E':
        case 'F':
        case 'G':
            out->flags |= FORMAT_FLAG_UPPER;
            __fallthrough;
        case 'e':
        case 'f':
        case 'g':
            out->conversion = 'f';
            break;

        case 'u':
            out->flags |= FORMAT_FLAG_UNSIGNED;
            __fallthrough;
        case 'd':
        case 'i':
            out->base = 10;
            out->conversion = 'd';
            break;

        case 'c':
            out->conversion = 'c';
            break;

        case 's':
            out->conversion = 's';
            break;

        default:
            return -EILSEQ;
    }

    return (int)(fmt - start);
}

int format_process(FormatProc_t *proc, const char *fmt, va_list args) {    
    if ((proc == NULL) || (fmt == NULL)) {
        return -(int)EINVAL;
    }

    while (*fmt != '\0') {
        char ch = *fmt++;
        if (ch == '%') {
            FormatConv_t conv;
            int ret = format_convertion(fmt, &conv);
            if (ret < 0) {
                return ret;
            }
            fmt += ret;

            // use dynamic width
            if ((conv.width_present) && (conv.width == -1)) {
                conv.width = va_arg(args, int);
            }
            // use dynamic precision
            if ((conv.precision_present) && (conv.precision == -1)) {
                conv.precision = va_arg(args, int);
            }
            
            switch(conv.conversion) {
                case 'd': {
                    int64_t num;
                    if (conv.size == FORMAT_SIZE_LL) {
                        num = (int64_t) va_arg(args, int32_t);
                    } else {
                        num = (int64_t) va_arg(args, int64_t);
                    }
                    ret = format_integer(proc->tmp_buf, conv.base, conv.flags, num);
                    if (ret < 0) {
                        return ret;
                    } else {
                        proc->write(proc, proc->tmp_buf, (size_t)ret);
                        proc->cur_out += ret;
                    }   
                    break;
                }  
                case 'f': {
                    // va_arg promotes float to double when passed through '...'
                    double num = va_arg(args, double);
                    ret = format_fractional(proc->tmp_buf, conv.flags, num);
                    if (ret < 0) {
                        return ret;
                    } else {
                        proc->write(proc, proc->tmp_buf, (size_t)ret);
                        proc->cur_out += ret;
                    }   
                    break;                    
                }
                case 's': {
                    const char *str = va_arg(args, char *);
                    if (str == NULL) {
                        str = "(null)";
                    }
                    size_t len = strlen(str);
                    proc->write(proc, str, len);
                    proc->cur_out += len;
                    break;
                }
                case 'c': {
                    // va_arg promotes char to int when passed through '...'
                    char ch = (char) va_arg(args, int);
                    proc->write(proc, &ch, 1);
                    proc->cur_out += 1;
                    break;
                }
                default:
                    // This should never happen since format_convertion should have rejected it
                    return -EILSEQ;
            }
        } else {
            char ch = (char) va_arg(args, int);
            proc->write(proc, &ch, 1);
            proc->cur_out += 1;
        }
    }

    return proc->cur_out;
}
