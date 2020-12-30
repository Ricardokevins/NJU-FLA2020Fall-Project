; first to design a tm to check the string distribute
#Q = {0,q_cp_multiplier1,q_multiply,q_reset,q_cp_multiplier2,q_check,q_reset_result,accept,accept2,accept3,accept4,leftreject,rightreject,reject2,reject3,reject4,reject5,halt_reject,halt_accept}

#S = {1,x,=}

#G = {1,x,=,_,t,r,u,e,f,a,l,s}

#q0 = 0

#B = _

#F = {halt_accept}

#N = 3

0 1__ _1_ rr* q_cp_multiplier1
0 ___ ___ *** rightreject

q_cp_multiplier1 1__ _1_ rr* q_cp_multiplier1
q_cp_multiplier1 x__ ___ rl* q_multiply
q_cp_multiplier1 =__ =__ *** rightreject

q_multiply 11_ 11_ *** q_reset
q_multiply =1_ _1_ r*l q_reset_result
q_multiply _1_ 1__ *** rightreject
q_multiply x1_ x__ *** rightreject

q_reset 11_ 11_ *l* q_reset
q_reset 1__ 1__ *r* q_cp_multiplier2

q_cp_multiplier2 11_ 111 *rr q_cp_multiplier2
q_cp_multiplier2 1__ ___ rl* q_multiply

q_reset_result 111 111 **l q_reset_result
q_reset_result 11_ 11_ **r q_check
q_reset_result =11 =__ *** rightreject
q_reset_result x11 x__ *** rightreject
q_reset_result _11 ___ *** rightreject

q_check 111 _1_ r*r q_check
q_check 11_ 1__ *** rightreject

; other string behind
q_check =1_ =__ *** rightreject
q_check x1_ x__ *** rightreject

q_check _11 ___ *** rightreject
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