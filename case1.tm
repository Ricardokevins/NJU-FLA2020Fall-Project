; first to design a tm to check the string distribute
#Q = {0,qa,qab,qaba,qabab,accept3,accept4}

#S = {a,b}

#G = {a,b,c,_}

#q0 = 0

#B = _

#F = {halt_accept}

#N = 3

0 a__ _a_ rr* qa
qa a__ _a_ rr* qa
qa b__ b__ *** qab
qab b__ __b r*r qab
qab a__ a__ *l* qaba
qaba aa_ ___ rl* qaba
qaba b__ b__ **l qabab
qabab b_b ___ r*l qabab
qabab ___ ___ *** accept

accept ___ t__ r** accept2
accept2 ___ r__ r** accept3
accept3 ___ u__ r** accept4
accept4 ___ e__ *** halt_accept