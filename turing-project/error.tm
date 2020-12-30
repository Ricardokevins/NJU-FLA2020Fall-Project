; 1.first copy the multiplier1 to tape2
; 2.Then check the symbol 'x' to continue on step3
; 3.go through multiplier2. And write multiplier1 on tape3 for every '1' in multiplier2
; 4.Check the token '=' and continue on step5
; 5.erase '1' on tape1 and tape3 
; 6.Hit here with empty tape1 and tape3 To Hit accept state

; q_cp_multiplier1 ---> copy multiplier1 to tape2
; q_multiply ---> Going on step3&4 (Work with following state)
; q_reset ---> Reset RWhead on tape2 (RWhead:Read and Write Head)
; q_cp_multiplier2 ---> copy multiplier1(tape2) to tape3
; q_reset_result ---> reset RWhead on tape3 to its Start point
; q_check ---> Step5 
; state with "accept" and "reject" is needed to print result
; use rightreject to erase content of the right part and print false
; use leftreject to erase content of the left part and print false

#Q = {0,q_cp_multiplier1,q_multiply,q_reset,q_cp_multiplier2,q_check,q_reset_result,accept,accept2,accept3,accept4,leftreject,rightreject,reject2,reject3,reject4,reject5,halt_reject,halt_accept}

#S = {1,x,=}

#G = {1,x,=,_,t,r,u,e,f,a,l,s}

#q0 = 0

#B = _

#F = {halt_accept}

#N = 3

; meet 1 ---> start to copy multiplier1
; meet _ ---> empty string to reject
; meet x ---> wrong format to reject
; meet = ---> wrong format to reject
0 1__ _1_ rr* q_cp_multiplier1
0 ___ ___ *** rightreject
0 x__ x__ *** rightreject
0 =__ =__ *** rightreject

; meet 1 ---> continue to copy (step1)
; meet x ---> hit step2 
; meet = ---> wrong format to reject. eg:11=11
; meet _ ---> wrong format to reject. eg:11
q_cp_multiplier1 1__ _1_ rr* q_cp_multiplier1
q_cp_multiplier1 x__ ___ rl* q_multiply
q_cp_multiplier1 =__ =__ *** rightreject
q_cp_multiplier1 ___ =__ *** rightreject

; meet 1 ---> '1' on tape1 to use q_reset to reset RWhead on tape2
; meet = ---> multiply finished and use q_reset_result to reset RWhead on tape3
; meet _1_ ---> no '=' in Input. eg:11x11
; meet x1_ ---> meet another x in Input. eg:11x11x11
q_multiply 11_ 11_ *** q_reset
q_multiply =1_ _1_ r*l q_reset_result
q_multiply _1_ 1__ *** rightreject
q_multiply x1_ x__ *** rightreject

; meet 11 ---> move RWhead on tape2
; meet 1_ ---> RWhead on tape2 hit the start point and start to copy
q_reset 11_ 11_ *l* q_reset
q_reset 1__ 1__ *r* q_cp_multiplier2

; meet 11_ ---> continue to copy to tape3
; meet 1__ ---> '1' on tape2 run out. Try to move RWhead on tape1 to next '1' and return to q_multiply
q_cp_multiplier2 11_ 111 *rr q_cp_multiplier2
q_cp_multiplier2 1__ ___ rl* q_multiply

; meet '111' ---> move RWhead on tape3 to its start point
; meet '11_' ---> already move to start point and turn to step5
; meet '=11' ---> more = on tape1. eg:11x11==11
; meet 'x11' ---> more x on tape1. eg:11x11=x11
; meet '_11' ---> no answer string detected. eg:11x11=
q_reset_result 111 111 **l q_reset_result
q_reset_result 11_ 11_ **r q_check
q_reset_result =11 =__ *** rightreject
q_reset_result x11 x__ *** rightreject
q_reset_result _11 ___ *** rightreject

; meet '111' ---> continue Step5
; meet '11_' ---> '1' on tape3 Less than '1' on tape1
q_check 111 _1_ r*r q_check
; meet _11 ---> '1' on tape1 Less than '1' on tape3
q_check _11 ___ *** rightreject

q_check 11_ 1__ *** rightreject

; meet '=' ---> more '=' afterward Hit reject
; meet 'x' ---> more 'x' afterward Hit reject
q_check =1_ =__ *** rightreject
q_check x1_ x__ *** rightreject
q_check =11 =__ *** rightreject
q_check x11 x__ *** rightreject
; meet _1_ ---> go to step6
q_check _1_ ___ *** accept

accept ___ t__ r** accept2
accept2 ___ r__ r** accept3
accept3 ___ u__ r** accept4
accept4 ___ e__ *** halt_accept

leftreject 1__ ___ l** leftreject
leftreject =__ ___ l** leftreject
leftreject x__ ___ l** leftreject
leftreject ___ f__ r** reject2

rightreject 1__ ___ r** rightreject
rightreject =__ ___ r** rightreject
rightreject x__ ___ r** rightreject
rightreject ___ f__ r** reject2

reject2 ___ a__ r** reject3
reject3 ___ l__ r** reject4
reject4 ___ s__ r** reject5
reject5 ___ e__ *** halt_reject