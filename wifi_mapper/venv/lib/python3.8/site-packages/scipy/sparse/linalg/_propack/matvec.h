c
c     (C) Rasmus Munk Larsen, Stanford University, 2004
c


      integer mmax,nmax,kmax,nnzmax
      integer densemmax, densenmax
      parameter(densemmax=1000,densenmax=1000)
      parameter(mmax=5000,nmax=5000,kmax=1000)
      parameter(nnzmax=densemmax*densenmax)
      integer colptr(nmax+1), rowind(nnzmax), nrow , ncol, nnzero
      integer matform, coordinate(nnzmax,2)
      complex values(nnzmax), matrix(densemmax,densenmax)
      equivalence(values,matrix)
      common/hb/matrix,colptr,rowind,nrow,ncol,nnzero,coordinate,matform
