section .text
;;
;; @brief      Arbitrary function to demonstrate SIMD instructions
;;
;; @details    This function operates on single precision arrays.
;;
;; @param      rdi contains first parameter to function (x).
;;             rsi contains second parameter to function (y).
;;
;; @return     Floating point result in memory location pointed to by rdi, which
;;             is parameter x.
;;
global sse
sse:
  movdqa xmm0, [rdi]
  mulps	xmm0, [rsi]             ; xmm0 = x * y
  addps xmm0, [rsi]             ; xmm0 += y
  movdqa [rdi], xmm0            ; result pointed to by rdi which is x.
  ret
