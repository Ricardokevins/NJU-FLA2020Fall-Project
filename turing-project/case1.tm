; 1.first copy first part of "a" to tape2
; 2.then copy first part of "b" to tape3
; 3.erase "a" both on tape1 and tape2
; 4.erase "b" both on tape1 and tape3
; Accept when hit here with no more content on tape1

; qa means step1 above
; qab means step2 above
; qaba means step3 above
; qabab mesns step4 above
; state with "accept" and "reject" is needed to print result
; use rightreject to erase content of the right part and print false
; use leftreject to erase content of the left part and print false

#Q = {0,qa,qab,qaba,qabab,accept,accept2,accept3,accept4,leftreject,rightreject,reject2,reject3,reject4,reject5,halt_reject,halt_accept}

#S = {a,b}

#G = {a,b,_,t,r,u,e,f,a,l,s}

#q0 = 0

#B = _

#F = {halt_accept}

#N = 3

; 3 cases , Input string start with a ---> is right. Input string start with B or b ----> Hit reject
0 a__ _a_ rr* qa
0 ___ ___ *** rightreject
0 b__ b__ *** rightreject

; meet a ----> copy it
; meet b ----> change to step2
; meet empty ----> string is "aaa" hit reject
qa a__ _a_ rr* qa
qa b__ b__ *** qab
qa ___ ___ *** leftreject ; fix case:aaa

; meet b ---->continue to copy
; meet a ---->change to step3
; meet empty ---> string is "aab" hit reject
qab b__ __b r*r qab
qab a__ a__ *l* qaba
qab ___ ___ *** leftreject ; fix case:aaabb

; meet aa ---> continue to erase
; meet b_ ---> tape1 and tape2's 'a' is clear
; meet a_ ---> tape1 remains 'a' but tape2 is clear Hit reject
; meet _a ---> tape2 remains 'a' but tape1 is clear. Just like aaabbaaaa
; meet ba ---> tape2's a is clear and meet b. But tape2 remains a. Like aaabbaaaab
; meet __ ---> although tape1 and tape2 both empty but Hit reject. Just like aaabbaaa
qaba aa_ ___ rl* qaba
qaba b__ b__ **l qabab
qaba a__ a__ *** rightreject ; to less a in pre
qaba _a_ ___ *** leftreject ;  to much a in pre and no b after
qaba ba_ b__ *** rightreject ; to much a in pre
qaba ___ ___ *** rightreject

; meet b_b ---> continue to erase tape1 and tape3's "b"
; meet ___ ---> Ohhhhhh tape1,2,3 both clear means Accept
; meet b__ ---> tape1 remains "b",like aabbbaab
; meet __b ---> tape3 remains "b",like aabbaabbb
; meet a__ ---> there are "a" behind the last part of "b" Hit reject
qabab b_b ___ r*l qabab
qabab ___ ___ *** accept
qabab b__ b__ *** rightreject ; too less b in previous
qabab __b ___ *** leftreject ; too much b in previous
qabab a__ a__ *** rightreject ;left string on tape


; This state are used to write 'true' on tape1
accept ___ t__ r** accept2
accept2 ___ r__ r** accept3
accept3 ___ u__ r** accept4
accept4 ___ e__ *** halt_accept

; Reject with first erase the tape1 and then write false on it
leftreject a__ ___ l** leftreject
leftreject b__ ___ l** leftreject
leftreject ___ f__ r** reject2

rightreject a__ ___ r** rightreject
rightreject b__ ___ r** rightreject
rightreject ___ f__ r** reject2

reject2 ___ a__ r** reject3
reject3 ___ l__ r** reject4
reject4 ___ s__ r** reject5
reject5 ___ e__ *** halt_reject