%define lw 0

;;
;; @brief      Macro used to create dictionary words.
;;
;; @details    Macro used to create a dictionary statically as a list with each
;;             newly defined element prepended to it. Each entry starts with a
;;             pointer to the next entry, then holds a key as a null-terminated
;;             string.
;;
;; @param      %1 is the dictionary key in quotes.
;;             %2 is the assembly language label name.
;;
%macro colon 2
%%lw: dq lw
  db %1, 0
xt_ %+ %2:

%define lw %%lw
%endmacro
