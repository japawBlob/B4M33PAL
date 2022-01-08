#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

unsigned long Amin, Amax, Cmin, Cmax, Mmin, Mmax;
int P;

std::set<unsigned long> getFactors(unsigned long n) {
        std::set<unsigned long> ret;
        unsigned long z = 2;
        while (z * z <= n) {
                if (n % z == 0) {
                        ret.insert(z);
                        n /= z;
                } else {
                        z++;
                }
        }
        if (n > 1) {
                ret.insert(n);
        }
        return ret;
}

bool isAdivisible(unsigned long A,unsigned long M, std::set<unsigned long> factorsM){
        A--;
        for(auto prime : factorsM){
                if(A%prime != 0){
                        return false;
                }
        }
        return true;
}

bool theMighty4(unsigned long A,unsigned long M){
        A--;
        if( M%4 == 0 && A%4 != 0){
                return false;
        }
        return true;
}

bool checkMaxPeriod(unsigned long A,unsigned long C,unsigned long M, std::set<unsigned long> factorsM){
        if (theMighty4(A,M) && std::__gcd(C,M) == 1 && isAdivisible(A,M,factorsM)){
                return true;
        }
        return false;
}

int main (){
        scanf("%lu %lu %lu %lu %lu %lu %i", &Amin, &Amax, &Cmin, &Cmax, &Mmin, &Mmax, &P);

        //std::cout << Amin << " " << Amax << " " << Cmin<< " " << Cmax<< " " << Mmin<< " " << Mmax<< " " << P << " \n";

        unsigned long maxPeriodCount = 0;

        /*for (auto blob : getFactors(99)) {
                std::cout << blob << " ";
        } std::cout << "\n";*/


        for (unsigned long m = Mmin; m <= Mmax; ++m) {
                auto factorsM = getFactors(m);
                if (factorsM.size() != P){
                        continue;
                }
                for (unsigned long c = Cmin; c <= Cmax; ++c) {
                        getFactors(c);
                        for (unsigned long a = Amin; a <= Amax; ++a) {
                                if(checkMaxPeriod(a,c,m,factorsM)){
                                        maxPeriodCount++;
                                }
                        }
                }
        }
        std::cout << maxPeriodCount << "\n";
        return 0;
}