// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2017 Alec Jacobson <alecjacobson@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include "unique_rows.h"
#include "sortrows.h"

#include <algorithm>
#include <iostream>
#include <map>


template <typename DerivedA, typename DerivedC, typename DerivedIA, typename DerivedIC>
IGL_INLINE void igl::unique_rows(
  const Eigen::DenseBase<DerivedA>& A,
  Eigen::PlainObjectBase<DerivedC>& C,
  Eigen::PlainObjectBase<DerivedIA>& IA,
  Eigen::PlainObjectBase<DerivedIC>& IC)
{
  using namespace std;
  using namespace Eigen;
  VectorXi IM;
  DerivedA sortA;
  sortrows(A,true,sortA,IM);


  const int num_rows = sortA.rows();
  const int num_cols = sortA.cols();
  vector<int> vIA(num_rows);
  for(int i=0;i<num_rows;i++)
  {
    vIA[i] = i;
  }

  auto index_equal = [&sortA, &num_cols](const size_t i, const size_t j) {
    for (size_t c=0; c<num_cols; c++) {
      if (sortA(i,c) != sortA(j,c))
        return false;
    }
    return true;
  };
  vIA.erase(
    std::unique(
    vIA.begin(),
    vIA.end(),
    index_equal
    ),vIA.end());

  IC.resize(A.rows(),1);
  {
    int j = 0;
    for(int i = 0;i<num_rows;i++)
    {
      if(sortA.row(vIA[j]) != sortA.row(i))
      {
        j++;
      }
      IC(IM(i,0),0) = j;
    }
  }
  const int unique_rows = vIA.size();
  C.resize(unique_rows,A.cols());
  IA.resize(unique_rows,1);
  // Reindex IA according to IM
  for(int i = 0;i<unique_rows;i++)
  {
    IA(i,0) = IM(vIA[i],0);
    C.row(i) = A.row(IA(i,0));
  }
}

#ifdef IGL_STATIC_LIBRARY
// Explicit template instantiation
template void igl::unique_rows<Eigen::Matrix<double, -1, 3, 1, -1, 3>, Eigen::Matrix<double, -1, 3, 1, -1, 3>, Eigen::Matrix<int, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1> >(Eigen::DenseBase<Eigen::Matrix<double, -1, 3, 1, -1, 3> > const&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, 3, 1, -1, 3> >&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> >&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> >&);
template void igl::unique_rows<Eigen::Matrix<double, -1, 3, 1, -1, 3>, Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1> >(Eigen::DenseBase<Eigen::Matrix<double, -1, 3, 1, -1, 3> > const&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> >&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> >&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> >&);
template void igl::unique_rows<Eigen::Matrix<int, -1, 1, 0, -1, 1>, Eigen::Matrix<int, -1, 1, 0, -1, 1>, Eigen::Matrix<int, -1, 1, 0, -1, 1>, Eigen::Matrix<int, -1, 1, 0, -1, 1> >(Eigen::DenseBase<Eigen::Matrix<int, -1, 1, 0, -1, 1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, 1, 0, -1, 1> >&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, 1, 0, -1, 1> >&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, 1, 0, -1, 1> >&);
template void igl::unique_rows<Eigen::Matrix<double,-1,-1,0,-1,-1>,Eigen::Matrix<double,-1,-1,0,-1,-1>,Eigen::Matrix<int,-1,-1,0,-1,-1>,Eigen::Matrix<int,-1,-1,0,-1,-1> >(Eigen::DenseBase<Eigen::Matrix<double,-1,-1,0,-1,-1> > const&,Eigen::PlainObjectBase<Eigen::Matrix<double,-1,-1,0,-1,-1> >&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,-1,0,-1,-1> >&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,-1,0,-1,-1> >&);
template void igl::unique_rows<Eigen::Matrix<double,-1,-1,0,-1,-1>,Eigen::Matrix<double,-1,-1,0,-1,-1>,Eigen::Matrix<int,-1,1,0,-1,1>,Eigen::Matrix<int,-1,1,0,-1,1> >(Eigen::DenseBase<Eigen::Matrix<double,-1,-1,0,-1,-1> > const&,Eigen::PlainObjectBase<Eigen::Matrix<double,-1,-1,0,-1,-1> >&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,1,0,-1,1> >&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,1,0,-1,1> >&);
template void igl::unique_rows<Eigen::Matrix<double,-1,-1,0,-1,-1>,Eigen::Matrix<double,-1,-1,0,-1,-1>,Eigen::Matrix<long,-1,1,0,-1,1>,Eigen::Matrix<long,-1,1,0,-1,1> >(Eigen::DenseBase<Eigen::Matrix<double,-1,-1,0,-1,-1> > const&,Eigen::PlainObjectBase<Eigen::Matrix<double,-1,-1,0,-1,-1> >&,Eigen::PlainObjectBase<Eigen::Matrix<long,-1,1,0,-1,1> >&,Eigen::PlainObjectBase<Eigen::Matrix<long,-1,1,0,-1,1> >&);
template void igl::unique_rows<Eigen::Matrix<double,-1,-1,1,-1,-1>,Eigen::Matrix<double,-1,-1,1,-1,-1>,Eigen::Matrix<int,-1,1,0,-1,1>,Eigen::Matrix<int,-1,1,0,-1,1> >(Eigen::DenseBase<Eigen::Matrix<double,-1,-1,1,-1,-1> > const&,Eigen::PlainObjectBase<Eigen::Matrix<double,-1,-1,1,-1,-1> >&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,1,0,-1,1> >&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,1,0,-1,1> >&);
template void igl::unique_rows<Eigen::Matrix<double,-1,3,0,-1,3>,Eigen::Matrix<double,-1,3,0,-1,3>,Eigen::Matrix<int,-1,1,0,-1,1>,Eigen::Matrix<int,-1,1,0,-1,1> >(Eigen::DenseBase<Eigen::Matrix<double,-1,3,0,-1,3> > const&,Eigen::PlainObjectBase<Eigen::Matrix<double,-1,3,0,-1,3> >&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,1,0,-1,1> >&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,1,0,-1,1> >&);
template void igl::unique_rows<Eigen::Matrix<double,-1,3,0,-1,3>,Eigen::Matrix<double,-1,3,0,-1,3>,Eigen::Matrix<long,-1,1,0,-1,1>,Eigen::Matrix<long,-1,1,0,-1,1> >(Eigen::DenseBase<Eigen::Matrix<double,-1,3,0,-1,3> > const&,Eigen::PlainObjectBase<Eigen::Matrix<double,-1,3,0,-1,3> >&,Eigen::PlainObjectBase<Eigen::Matrix<long,-1,1,0,-1,1> >&,Eigen::PlainObjectBase<Eigen::Matrix<long,-1,1,0,-1,1> >&);
template void igl::unique_rows<Eigen::Matrix<float,-1,3,0,-1,3>,Eigen::Matrix<float,-1,-1,0,-1,-1>,Eigen::Matrix<int,-1,-1,0,-1,-1>,Eigen::Matrix<int,-1,-1,0,-1,-1> >(Eigen::DenseBase<Eigen::Matrix<float,-1,3,0,-1,3> > const&,Eigen::PlainObjectBase<Eigen::Matrix<float,-1,-1,0,-1,-1> >&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,-1,0,-1,-1> >&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,-1,0,-1,-1> >&);
template void igl::unique_rows<Eigen::Matrix<float,-1,3,0,-1,3>,Eigen::Matrix<float,-1,3,0,-1,3>,Eigen::Matrix<int,-1,-1,0,-1,-1>,Eigen::Matrix<int,-1,-1,0,-1,-1> >(Eigen::DenseBase<Eigen::Matrix<float,-1,3,0,-1,3> > const&,Eigen::PlainObjectBase<Eigen::Matrix<float,-1,3,0,-1,3> >&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,-1,0,-1,-1> >&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,-1,0,-1,-1> >&);
template void igl::unique_rows<Eigen::Matrix<float,-1,3,1,-1,3>,Eigen::Matrix<float,-1,-1,0,-1,-1>,Eigen::Matrix<int,-1,-1,0,-1,-1>,Eigen::Matrix<int,-1,-1,0,-1,-1> >(Eigen::DenseBase<Eigen::Matrix<float,-1,3,1,-1,3> > const&,Eigen::PlainObjectBase<Eigen::Matrix<float,-1,-1,0,-1,-1> >&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,-1,0,-1,-1> >&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,-1,0,-1,-1> >&);
template void igl::unique_rows<Eigen::Matrix<float,-1,3,1,-1,3>,Eigen::Matrix<float,-1,3,1,-1,3>,Eigen::Matrix<int,-1,-1,0,-1,-1>,Eigen::Matrix<int,-1,-1,0,-1,-1> >(Eigen::DenseBase<Eigen::Matrix<float,-1,3,1,-1,3> > const&,Eigen::PlainObjectBase<Eigen::Matrix<float,-1,3,1,-1,3> >&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,-1,0,-1,-1> >&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,-1,0,-1,-1> >&);
template void igl::unique_rows<Eigen::Matrix<int,-1,-1,0,-1,-1>,Eigen::Matrix<int,-1,-1,0,-1,-1>,Eigen::Matrix<int,-1,-1,0,-1,-1>,Eigen::Matrix<int,-1,1,0,-1,1> >(Eigen::DenseBase<Eigen::Matrix<int,-1,-1,0,-1,-1> > const&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,-1,0,-1,-1> >&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,-1,0,-1,-1> >&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,1,0,-1,1> >&);
template void igl::unique_rows<Eigen::Matrix<int,-1,-1,0,-1,-1>,Eigen::Matrix<int,-1,-1,0,-1,-1>,Eigen::Matrix<int,-1,1,0,-1,1>,Eigen::Matrix<int,-1,-1,0,-1,-1> >(Eigen::DenseBase<Eigen::Matrix<int,-1,-1,0,-1,-1> > const&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,-1,0,-1,-1> >&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,1,0,-1,1> >&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,-1,0,-1,-1> >&);
template void igl::unique_rows<Eigen::Matrix<int,-1,-1,0,-1,-1>,Eigen::Matrix<int,-1,-1,0,-1,-1>,Eigen::Matrix<int,-1,1,0,-1,1>,Eigen::Matrix<int,-1,1,0,-1,1> >(Eigen::DenseBase<Eigen::Matrix<int,-1,-1,0,-1,-1> > const&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,-1,0,-1,-1> >&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,1,0,-1,1> >&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,1,0,-1,1> >&);
template void igl::unique_rows<Eigen::Matrix<int,-1,-1,0,-1,-1>,Eigen::Matrix<int,-1,-1,0,-1,-1>,Eigen::Matrix<long,-1,1,0,-1,1>,Eigen::Matrix<long,-1,1,0,-1,1> >(Eigen::DenseBase<Eigen::Matrix<int,-1,-1,0,-1,-1> > const&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,-1,0,-1,-1> >&,Eigen::PlainObjectBase<Eigen::Matrix<long,-1,1,0,-1,1> >&,Eigen::PlainObjectBase<Eigen::Matrix<long,-1,1,0,-1,1> >&);
template void igl::unique_rows<Eigen::Matrix<int,-1,2,0,-1,2>,Eigen::Matrix<int,-1,2,0,-1,2>,Eigen::Matrix<int,-1,1,0,-1,1>,Eigen::Matrix<int,-1,1,0,-1,1> >(Eigen::DenseBase<Eigen::Matrix<int,-1,2,0,-1,2> > const&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,2,0,-1,2> >&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,1,0,-1,1> >&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,1,0,-1,1> >&);
template void igl::unique_rows<Eigen::Matrix<int,-1,2,0,-1,2>,Eigen::Matrix<int,-1,2,0,-1,2>,Eigen::Matrix<long,-1,1,0,-1,1>,Eigen::Matrix<long,-1,1,0,-1,1> >(Eigen::DenseBase<Eigen::Matrix<int,-1,2,0,-1,2> > const&,Eigen::PlainObjectBase<Eigen::Matrix<int,-1,2,0,-1,2> >&,Eigen::PlainObjectBase<Eigen::Matrix<long,-1,1,0,-1,1> >&,Eigen::PlainObjectBase<Eigen::Matrix<long,-1,1,0,-1,1> >&);
#ifdef WIN32
template void igl::unique_rows<class Eigen::Matrix<int, -1, -1, 0, -1, -1>, class Eigen::Matrix<__int64, -1, 1, 0, -1, 1>, class Eigen::Matrix<__int64, -1, 1, 0, -1, 1> >(class Eigen::DenseBase<class Eigen::Matrix<int, -1, -1, 0, -1, -1> > const &, class Eigen::PlainObjectBase<class Eigen::Matrix<int, -1, -1, 0, -1, -1> > &, class Eigen::PlainObjectBase<class Eigen::Matrix<__int64, -1, 1, 0, -1, 1> > &, class Eigen::PlainObjectBase<class Eigen::Matrix<__int64, -1, 1, 0, -1, 1> > &);
template void igl::unique_rows<class Eigen::Matrix<int,-1,-1,0,-1,-1>,class Eigen::Matrix<int,-1,-1,0,-1,-1>,class Eigen::Matrix<__int64,-1,1,0,-1,1>,class Eigen::Matrix<__int64,-1,1,0,-1,1> >(class Eigen::DenseBase<class Eigen::Matrix<int,-1,-1,0,-1,-1> > const &,class Eigen::PlainObjectBase<class Eigen::Matrix<int,-1,-1,0,-1,-1> > &,class Eigen::PlainObjectBase<class Eigen::Matrix<__int64,-1,1,0,-1,1> > &,class Eigen::PlainObjectBase<class Eigen::Matrix<__int64,-1,1,0,-1,1> > &);
#endif
#endif
