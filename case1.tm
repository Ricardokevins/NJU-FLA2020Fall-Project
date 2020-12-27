; first to design a tm to check the string distribute
#Q = {0,qa,qab,qaba,qabab,accept,accept2,accept3,accept4,leftreject,rightreject,reject2,reject3,reject4,reject5,halt_reject}

#S = {a,b}

#G = {a,b,c,_}

#q0 = 0

#B = _

#F = {halt_accept}

#N = 3

0 a__ _a_ rr* qa
0 ___ ___ *** rightreject
0 b__ b__ *** rightreject

qa a__ _a_ rr* qa
qa b__ b__ *** qab
qa ___ ___ *** leftreject ; fix case:aaa

qab b__ __b r*r qab
qab a__ a__ *l* qaba
qab ___ ___ *** leftreject ; fix case:aaabb

qaba aa_ ___ rl* qaba
qaba b__ b__ **l qabab
qaba a__ a__ *** rightreject ; to less a in ore
qaba _a_ ___ *** leftreject ;  to much a in pre and no b after
qaba ba_ b__ *** rightreject ; to much a in pre
qaba ___ ___ *** rightreject

qabab b_b ___ r*l qabab
qabab ___ ___ *** accept
qabab b__ b__ *** rightreject ; too less b in previous
qabab __b ___ *** leftreject ; too much b in previous
qabab a__ a__ *** rightreject ;left string on tape


accept ___ t__ r** accept2
accept2 ___ r__ r** accept3
accept3 ___ u__ r** accept4
accept4 ___ e__ *** halt_accept

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