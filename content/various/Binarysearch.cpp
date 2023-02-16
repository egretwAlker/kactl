// a sorted array is stored as a[0], a[1], ..., a[n-1]
int l = -1, r = n;
while(r - l > 1) {
    int m = (l + r) / 2;
    if(k < a[m]) r = m; // a[l] <= k < a[m] <= a[r]
    else l = m; // a[l] <= a[m] <= k < a[r]   
}
//for a Search on arbitrary predicate we use
//f(i) is a boolean function such that f(0) <= ... <= f(n-1) we replace the if with if(f(m))
//---------------------
//for Continuous search:
for(double uu=Upper_limit ;uu>=Lower_limit ;uu/=2.0) // uu is upper bound
    if(check(l+uu)) l+=uu; //check is a bool function