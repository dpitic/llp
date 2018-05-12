;;
;; Header file for I/O library. This file declares all of the functions in the
;; I/O library, and must be included in any source file that uses the I/O
;; library.
;;
%ifndef _LIBLLP_INC_
%define _LIBLLP_INC_

extern string_length
extern print_string
extern print_error
extern print_char
extern print_newline
extern print_uint
extern print_int
extern string_equals
extern read_char
extern read_word
extern parse_uint
extern parse_int
extern string_copy
extern exit

%endif                          ; _LIBLLP_INC_
