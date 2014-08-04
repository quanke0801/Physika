/*
 * @file array_Nd_iterator-inl.h 
 * @brief  iterator of multi-dimensional array class.
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

#ifndef PHYSIKA_CORE_ARRAYS_ARRAY_ND_ITERATOR_INL_H_
#define PHYSIKA_CORE_ARRAYS_ARRAY_ND_ITERATOR_INL_H_

#include <cstdlib>
#include <iostream>

namespace Physika{

template <typename ElementType, int Dim>
ArrayNDIterator<ElementType,Dim>::ArrayNDIterator()
    :array_(NULL),element_idx_(0)
{
}

template <typename ElementType, int Dim>
ArrayNDIterator<ElementType,Dim>::~ArrayNDIterator()
{
}

template <typename ElementType, int Dim>
ArrayNDIterator<ElementType,Dim>::ArrayNDIterator(const ArrayNDIterator<ElementType,Dim> &iterator)
    :array_(iterator.array_),element_idx_(iterator.element_idx_)
{
}

template <typename ElementType, int Dim>
ArrayNDIterator<ElementType,Dim>& ArrayNDIterator<ElementType,Dim>::operator= (const ArrayNDIterator<ElementType,Dim> &iterator)
{
    array_ = iterator.array_;
    element_idx_ = iterator.element_idx_;
    return *this;
}

template <typename ElementType, int Dim>
bool ArrayNDIterator<ElementType,Dim>::operator== (const ArrayNDIterator<ElementType,Dim> &iterator) const
{
    if((array_==NULL)||(iterator.array_==NULL))
    {
        std::cerr<<"Error: undefined operator == for unintialized iterator!\n";
        std::exit(EXIT_FAILURE);
    }
    return (element_idx_ == iterator.element_idx_)&&(array_ == iterator.array_);
}

template <typename ElementType, int Dim>
bool ArrayNDIterator<ElementType,Dim>::operator!= (const ArrayNDIterator<ElementType,Dim> &iterator) const
{
    if((array_==NULL)||(iterator.array_==NULL))
    {
        std::cerr<<"Error: undefined operator != for unintialized iterator!\n";
        std::exit(EXIT_FAILURE);
    }
    return (element_idx_ != iterator.element_idx_)||(array_ != iterator.array_);
}

template <typename ElementType, int Dim>
ArrayNDIterator<ElementType,Dim>& ArrayNDIterator<ElementType,Dim>::operator++ ()
{
    if(array_==NULL)
    {
        std::cerr<<"Error: undefined operator ++ for uninitialized iterator!\n";
        std::exit(EXIT_FAILURE);
    }
    ++element_idx_;
    return *this;
}

template <typename ElementType, int Dim>
ArrayNDIterator<ElementType,Dim>& ArrayNDIterator<ElementType,Dim>::operator-- ()
{
    if(array_==NULL)
    {
        std::cerr<<"Error: undefined operator -- for uninitialized iterator!\n";
        std::exit(EXIT_FAILURE);
    }
    --element_idx_;
    return *this;
}

template <typename ElementType, int Dim>
ArrayNDIterator<ElementType,Dim> ArrayNDIterator<ElementType,Dim>::operator++ (int)
{
    if(array_==NULL)
    {
        std::cerr<<"Error: undefined operator ++ for uninitialized iterator!\n";
        std::exit(EXIT_FAILURE);
    }
    ArrayIterator<ElementType> iterator(*this);
    ++element_idx_;
    return iterator;
}

template <typename ElementType, int Dim>
ArrayNDIterator<ElementType,Dim> ArrayNDIterator<ElementType,Dim>::operator-- (int)
{
    if(array_==NULL)
    {
        std::cerr<<"Error: undefined operator -- for uninitialized iterator!\n";
        std::exit(EXIT_FAILURE);
    }
    ArrayIterator<ElementType> iterator(*this);
    --element_idx_;
    return iterator;
}

template <typename ElementType, int Dim>
ArrayNDIterator<ElementType,Dim> ArrayNDIterator<ElementType,Dim>::operator+ (int stride) const
{
    if(array_==NULL)
    {
        std::cerr<<"Error: undefined operator + for uninitialized iterator!\n";
        std::exit(EXIT_FAILURE);
    }
    ArrayNDIterator<ElementType,Dim> iterator(*this);
    iterator.element_idx_ += stride;
    return iterator;
}

template <typename ElementType, int Dim>
ArrayNDIterator<ElementType,Dim> ArrayNDIterator<ElementType,Dim>::operator- (int stride) const
{
    if(array_==NULL)
    {
        std::cerr<<"Error: undefined operator - for uninitialized iterator!\n";
        std::exit(EXIT_FAILURE);
    }
    ArrayNDIterator<ElementType,Dim> iterator(*this);
    iterator.element_idx_ -= stride;
    return iterator;
}

template <typename ElementType, int Dim>
const ElementType& ArrayNDIterator<ElementType,Dim>::operator *() const
{
    if(array_==NULL)
    {
        std::cerr<<"Error: undefined operator * for uninitialized iterator!\n";
        std::exit(EXIT_FAILURE);
    }
    if(element_idx_ >= array_->totalElementCount())
    {
        std::cerr<<"Error: iterator out of range!\n";
        std::exit(EXIT_FAILURE);
    }
    return array_->data_[element_idx_];
}

template <typename ElementType, int Dim>
ElementType& ArrayNDIterator<ElementType,Dim>::operator *()
{
    if(array_==NULL)
    {
        std::cerr<<"Error: undefined operator * for uninitialized iterator!\n";
        std::exit(EXIT_FAILURE);
    }
    if(element_idx_ >= array_->totalElementCount())
    {
        std::cerr<<"Error: iterator out of range!\n";
        std::exit(EXIT_FAILURE);
    }
    return array_->data_[element_idx_];
}

}  //end of namespace Physika

#endif  //PHYSIKA_CORE_ARRAYS_ARRAY_ND_ITERATOR_INL_H_
