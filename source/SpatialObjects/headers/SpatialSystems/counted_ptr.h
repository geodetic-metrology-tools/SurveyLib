/*
 * SPDX-FileCopyrightText: 1998, 1999 Mark E. <snowball3@usa.net>
 *
 * SPDX-License-Identifier: LicenseRef-countedPrt
 */

#ifndef __RC_PTRS_H
#define __RC_PTRS_H

/*
  This header contains the classes counted_ptr 
  This class implements a reference-counted smart pointer that automatically
  deletes the pointer it contains when no longer needed
  i.e. (reference count drops to zero)
*/

#include <stddef.h>

template <class X>

/*!\ingroup spatialobjects
	@{*/

//! class implements a reference-counted smart pointer
class counted_ptr
{
//
// Public typedefs
//
public:
  typedef X element_type;
  typedef X* pointer_type;
  typedef size_t size_type;

public:
  explicit counted_ptr(X* p=0) : ptr(p)
  {
    count=new size_type(1);
  }

  counted_ptr (const counted_ptr<X> &r)
  {
    ptr=r.ptr;
    count=r.count;
    acquire();
  }

  ~counted_ptr() { release(); }

	counted_ptr& operator= (const counted_ptr<X> &r)
	{
    if (this != &r)
    {
      release();
      ptr = r.ptr;
      count = r.count;
      acquire();
    }
    return *this;
  }

  X& operator* () const { return *ptr; }
  X* get () const { return ptr; }
  X* operator-> () const { return ptr; }

  bool unique () const
  {
    return *count==1;
  }

protected:
  X* ptr;
  size_type *count;

protected:
  void release()
  {
    if (count && --(*count)==0)
    {
      delete ptr;
      delete count;
    }
    ptr = 0;
    count = 0;
  }

  void acquire()
  {
    (*count) += 1;
  }


};
/*@}*/

#endif

