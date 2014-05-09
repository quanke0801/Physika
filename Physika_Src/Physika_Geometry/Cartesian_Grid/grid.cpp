/*
 * @file grid.cpp 
 * @brief definition of uniform grid, 2D/3D
 *        iterator of the grid is defined as well
 * @author Fei Zhu
 * 
 * This file is part of Physika, a versatile physics simulation library.
 * Copyright (C) 2013 Physika Group.
 *
 * This Source Code Form is subject to the terms of the GNU General Public License v2.0. 
 * If a copy of the GPL was not distributed with this file, you can obtain one at:
 * http://www.gnu.org/licenses/gpl-2.0.html
 *
 */

#include <cfloat>
#include "Physika_Core/Utilities/physika_assert.h"
#include "Physika_Geometry/Cartesian_Grid/grid.h"

namespace Physika{

template <typename Scalar,int Dim>
GridBase<Scalar,Dim>::GridBase()
{
}

template <typename Scalar,int Dim>
GridBase<Scalar,Dim>::GridBase(const Range<Scalar,Dim> &domain, int cell_num)
    :domain_(domain)
{
    PHYSIKA_ASSERT(cell_num>=0);
    cell_num_ = Vector<int,Dim>(cell_num);
    dx_ = domain_.edgeLengths()/cell_num;
}

template <typename Scalar,int Dim>
GridBase<Scalar,Dim>::GridBase(const Range<Scalar,Dim> &domain, const Vector<int,Dim> &cell_num)
    :domain_(domain)
{
    for(int i = 0; i < Dim; ++i)
	PHYSIKA_ASSERT(cell_num[i]>=0);
    cell_num_ = cell_num;
    Vector<Scalar,Dim> domain_size = domain_.edgeLengths();
    for(int i = 0; i < Dim; ++i)
	dx_[i] = domain_size[i]/cell_num_[i];
}

template <typename Scalar,int Dim>
GridBase<Scalar,Dim>::GridBase(const GridBase<Scalar,Dim> &grid)
    :domain_(grid.domain_),dx_(grid.dx_),cell_num_(grid.cell_num_)
{
}

template <typename Scalar,int Dim>
GridBase<Scalar,Dim>& GridBase<Scalar,Dim>::operator= (const GridBase<Scalar,Dim> &grid)
{
    domain_ = grid.domain();
    dx_ = grid.dX();
    cell_num_ = grid.cellNum();
    return *this;
}

template <typename Scalar,int Dim>
bool GridBase<Scalar,Dim>::operator== (const GridBase<Scalar,Dim> &grid) const
{
    return (domain_==grid.domain())&&(dx_==grid.dX())&&(cell_num_==grid.cellNum());
}

template <typename Scalar,int Dim>
const Range<Scalar,Dim>& GridBase<Scalar,Dim>::domain() const
{
    return domain_;
}

template <typename Scalar,int Dim>
const Vector<Scalar,Dim>& GridBase<Scalar,Dim>::dX() const
{
    return dx_;
}

template <typename Scalar,int Dim>
const Vector<Scalar,Dim>& GridBase<Scalar,Dim>::minCorner() const
{
    return domain_.minCorner();
}

template <typename Scalar,int Dim>
const Vector<Scalar,Dim>& GridBase<Scalar,Dim>::maxCorner() const
{
    return domain_.maxCorner();
}

template <typename Scalar,int Dim>
Scalar GridBase<Scalar,Dim>::minEdgeLength() const
{
    Scalar min_length =FLT_MAX;
    for(int i = 0; i < Dim; ++i)
	if(dx_[i]<min_length)
	    min_length = dx_[i];
    return min_length;
}

template <typename Scalar,int Dim>
Scalar GridBase<Scalar,Dim>::maxEdgeLength() const
{
    Scalar max_length =FLT_MIN;
    for(int i = 0; i < Dim; ++i)
	if(dx_[i]>max_length)
	    max_length = dx_[i];
    return max_length;
}

template <typename Scalar,int Dim>
const Vector<int,Dim>& GridBase<Scalar,Dim>::cellNum() const
{
    return cell_num_;
}

template <typename Scalar,int Dim>
Vector<int,Dim> GridBase<Scalar,Dim>::nodeNum() const
{
    return cell_num_+Vector<int,Dim>(1);
}

template <typename Scalar,int Dim>
Scalar GridBase<Scalar,Dim>::cellSize() const
{
    Scalar size = 1.0;
    for(int i = 0; i < Dim; ++i)
	size *= dx_[i];
    return size;
}

template <typename Scalar,int Dim>
Vector<Scalar,Dim> GridBase<Scalar,Dim>::node(const Vector<int,Dim> &index) const
{
    for(int i = 0; i < Dim; ++i)
    {
	PHYSIKA_ASSERT(index[i]>=0);
	PHYSIKA_ASSERT(index[i]<=cell_num_[i]);
    }
    Vector<Scalar,Dim> bias;
    for(int i = 0; i < Dim; ++i)
	bias[i] = index[i]*dx_[i];
    return domain_.minCorner()+bias;
}

template <typename Scalar,int Dim>
Vector<Scalar,Dim> GridBase<Scalar,Dim>::cellCenter(const Vector<int,Dim> &index) const
{
    for(int i = 0; i < Dim; ++i)
    {
	PHYSIKA_ASSERT(index[i]>=0);
	PHYSIKA_ASSERT(index[i]<cell_num_[i]);
    }
    Vector<Scalar,Dim> cor_node = node(index);
    return cor_node+0.5*dx_;
}

template <typename Scalar>
Vector<Scalar,2> Grid<Scalar,2>::node(int i, int j) const
{
    Vector<int,2> index(i,j);
    return GridBase<Scalar,2>::node(index);  //still wonder why this->node(index) doesn't work
}

template <typename Scalar>
Vector<Scalar,2> Grid<Scalar,2>::cellCenter(int i, int j) const
{
    Vector<int,2> index(i,j);
    return GridBase<Scalar,2>::cellCenter(index);
}

template <typename Scalar>
typename Grid<Scalar,2>::NodeIterator Grid<Scalar,2>::nodeBegin() const
{
    Grid<Scalar,2>::NodeIterator iterator;
    iterator.index_ = Vector<int,2>(0);
    iterator.grid_ = this;
}

template <typename Scalar>
typename Grid<Scalar,2>::NodeIterator Grid<Scalar,2>::nodeEnd() const
{
    Grid<Scalar,2>::NodeIterator iterator;
    iterator.index_ = Vector<int,2>(-1);
    iterator.grid_ = this;
}

template <typename Scalar>
typename Grid<Scalar,2>::CellIterator Grid<Scalar,2>::cellBegin() const
{
    Grid<Scalar,2>::CellIterator iterator;
    iterator.index_ = Vector<int,2>(0);
    iterator.grid_ = this;
}

template <typename Scalar>
typename Grid<Scalar,2>::CellIterator Grid<Scalar,2>::cellEnd() const
{
    Grid<Scalar,2>::CellIterator iterator;
    iterator.index_ = Vector<int,2>(-1);
    iterator.grid_ = this;
}

template <typename Scalar>
Vector<Scalar,3> Grid<Scalar,3>::node(int i, int j, int k) const
{
    Vector<int,3> index(i,j,k);
    return GridBase<Scalar,3>::node(index);
}

template <typename Scalar>
Vector<Scalar,3> Grid<Scalar,3>::cellCenter(int i, int j, int k) const
{
    Vector<int,3> index(i,j,k);
    return GridBase<Scalar,3>::cellCenter(index);
}

template <typename Scalar>
typename Grid<Scalar,3>::NodeIterator Grid<Scalar,3>::nodeBegin() const
{
    Grid<Scalar,3>::NodeIterator iterator;
    iterator.index_ = Vector<int,3>(0);
    iterator.grid_ = this;
}

template <typename Scalar>
typename Grid<Scalar,3>::NodeIterator Grid<Scalar,3>::nodeEnd() const
{
    Grid<Scalar,3>::NodeIterator iterator;
    iterator.index_ = Vector<int,3>(-1);
    iterator.grid_ = this;
}

template <typename Scalar>
typename Grid<Scalar,3>::CellIterator Grid<Scalar,3>::cellBegin() const
{
    Grid<Scalar,3>::CellIterator iterator;
    iterator.index_ = Vector<int,3>(0);
    iterator.grid_ = this;
}

template <typename Scalar>
typename Grid<Scalar,3>::CellIterator Grid<Scalar,3>::cellEnd() const
{
    Grid<Scalar,3>::CellIterator iterator;
    iterator.index_ = Vector<int,3>(-1);
    iterator.grid_ = this;
}

//explicit instantiation
template class Grid<float,2>;
template class Grid<float,3>;
template class Grid<double,2>;
template class Grid<double,3>;

} //end of namespace Physika






