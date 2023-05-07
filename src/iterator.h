#ifndef ITERATOR_H
#define ITERATOR_H

#include "basic.h"

MSTL_NAMESPACE_BEGIN

// STL迭代器定义

// STL中有五种迭代器类型
// Input Iterator               read only
// Output Iterator              write only
// Forward Iterator             允许"写入型"算法在其指向区间进行操作
// Bidirectional Iterator       提供双向访问能力
// Random Access Iterator       支持原生指针具有的全部能力

// 类型从属关系, 子类适用于接受父类类型的算法, 但是效率可能不佳
//
//              Input Iterator
//                    ↑
//             Forward Iterator
//                    ↑
//           Bidirectional Iterator
//                    ↑
//           Random Access Iterator

// 用于标记迭代器类型
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class T, class Distance>
struct input_iterator {
	typedef input_iterator_tag  iterator_category;
	typedef T                   value_type;
	typedef Distance            difference_type;
	typedef T*                  pointer;
	typedef T&                  reference;
};

struct output_iterator {
	typedef output_iterator_tag         iterator_category;
	typedef void                        value_type;
	typedef void                        difference_type;
	typedef void                        pointer;
	typedef void                        reference;
};

template <class T, class Distance>
struct forward_iterator {
	typedef forward_iterator_tag    iterator_category;
	typedef T                       value_type;
	typedef Distance                difference_type;
	typedef T*                      pointer;
	typedef T&                      reference;
};

template <class T, class Distance>
struct bidirectional_iterator {
	typedef bidirectional_iterator_tag  iterator_category;
	typedef T                           value_type;
	typedef Distance                    difference_type;
	typedef T*                          pointer;
	typedef T&                          reference;
};

template <class T, class Distance>
struct random_access_iterator {
	typedef random_access_iterator_tag  iterator_category;
	typedef T                           value_type;
	typedef Distance                    difference_type;
	typedef T*                          pointer;
	typedef T&                          reference;
};

template<class Category, class T, class Distance = ptrdiff_t,
    class Pointer = T*, class Reference = T&>
struct iterator
{
	typedef Category	iterator_category;
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
};

// 默认编译器支持 partial specialization of class templates (模板类偏特化)
// 即存在 __STL_CLASS_PARTIAL_SPECIALIZATION 定义
#define  __STL_CLASS_PARTIAL_SPECIALIZATION

#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION

// iterator_traits定义
// 用于萃取出迭代器所指对象的型别
template <class Iterator>
struct iterator_traits {

	// 迭代器类型, STL提供五种迭代器
	typedef typename Iterator::iterator_category iterator_category;

	// 迭代器所指对象的型别
	// 如果想与 STL 算法兼容, 那么在类内需要提供 value_type 定义
	typedef typename Iterator::value_type value_type;

	// 这个是用于处理两个迭代器间距离的类型
	typedef typename Iterator::difference_type difference_type;

	// 直接指向对象的原生指针类型
	typedef typename Iterator::pointer pointer;

	// 对象的引用类型
	typedef typename Iterator::reference reference;
};

// 针对指针提供的特化版本
template <class T>
struct iterator_traits<T*> {
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;
};

// 针对指向常对象的指针的特化版本
template <class T>
struct iterator_traits<const T*> {
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef const T* pointer;
    typedef const T& reference;
};

// iterator_traits支持函数

// iterator_category(const Iterator&)           返回迭代器类别
// distance_type(const Iterator&)               返回表示迭代器距离的类型
// value_type(const Iterator&)                  返回迭代器所指对象的类型

template<class Iterator>
inline typename iterator_traits<Iterator>::iterator_category iterator_category(const Iterator& It){
	typedef typename iterator_traits<Iterator>::iterator_category category;
	return category();
}
        
template<class Iterator>
inline typename iterator_traits<Iterator>::value_type* value_type(const Iterator& It){
	return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}
        
template<class Iterator>
inline typename iterator_traits<Iterator>::difference_type* difference_type(const Iterator& It){
	return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
}

#else /* __STL_CLASS_PARTIAL_SPECIALIZATION */

// 编译器不支持 partial specialization of class templates(模板类偏特化)
// 需要对所有迭代器类型都提供定义

template <class T, class Distance>
inline input_iterator_tag
iterator_category(const input_iterator<T, Distance>&) {
	return input_iterator_tag();
}

inline output_iterator_tag iterator_category(const output_iterator&) {
	return output_iterator_tag();
}

template <class T, class Distance>
inline forward_iterator_tag
iterator_category(const forward_iterator<T, Distance>&) {
	return forward_iterator_tag();
}

template <class T, class Distance>
inline bidirectional_iterator_tag
iterator_category(const bidirectional_iterator<T, Distance>&) {
	return bidirectional_iterator_tag();
}

template <class T, class Distance>
inline random_access_iterator_tag
iterator_category(const random_access_iterator<T, Distance>&) {
	return random_access_iterator_tag();
}

template <class T>
inline random_access_iterator_tag iterator_category(const T*) {
	return random_access_iterator_tag();
}

template <class T, class Distance>
inline T* value_type(const input_iterator<T, Distance>&) {
	return (T*)(0);
}

template <class T, class Distance>
inline T* value_type(const forward_iterator<T, Distance>&) {
	return (T*)(0);
}

template <class T, class Distance>
inline T* value_type(const bidirectional_iterator<T, Distance>&) {
	return (T*)(0);
}

template <class T, class Distance>
inline T* value_type(const random_access_iterator<T, Distance>&) {
	return (T*)(0);
}

template <class T>
inline T* value_type(const T*) {
	return (T*)(0);
}

template <class T, class Distance>
inline Distance* distance_type(const input_iterator<T, Distance>&) {
	return (Distance*)(0);
}

template <class T, class Distance>
inline Distance* distance_type(const forward_iterator<T, Distance>&) {
	return (Distance*)(0);
}

template <class T, class Distance>
inline Distance* distance_type(const bidirectional_iterator<T, Distance>&) {
	return (Distance*)(0);
}

template <class T, class Distance>
inline Distance* distance_type(const random_access_iterator<T, Distance>&) {
	return (Distance*)(0);
}

template <class T>
inline ptrdiff_t* distance_type(const T*) {
	return (ptrdiff_t*)(0);
}

#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

// template <class InputIterator, class Distance>
// inline void distance(InputIterator first, InputIterator last, Distance& n)

//                                distance
//                                   |
//                                   |---------------- 判断迭代器类型
//                 Input Iterator    ↓   Random Access Iterator
//               -------------------------------------------
//               |                                         |
//               |                                         |
//               ↓                                         |
// __distance(..., input_iterator_tag)                     |
// while (first != last) { ++first; ++n; }                 |
//                                                         ↓
//                                __distance(..., random_access_iterator_tag)
//                                n += last - first;

// distance() 定义亦有偏特化版本，此处未采用
// 采用模板类非偏特化版本

template <class InputIterator, class Distance>
inline void _distance(InputIterator first,
                     InputIterator last,
                     Distance& n,
                     input_iterator_tag) {
	while (first != last) {
		++first;
		++n;
	}
}

template <class RandomAccessIterator, class Distance>
inline void _distance(RandomAccessIterator first,
                     RandomAccessIterator last,
                     Distance& n,
                     random_access_iterator_tag) {
	n += last - first;
}

template <class InputIterator, class Distance>
inline void distance(InputIterator first, InputIterator last, Distance& n) {
	_distance(first, last, n, iterator_category(first));
}

// template <class InputIterator, class Distance>
// inline void advance(InputIterator& i, Distance n)

//                                advance
//                                   |
//                                   |---------------- 判断迭代器类型
//     Input Iterator                ↓
//   ---------------------------------------------------------------------
//   |             Random Access Iterator |      Bidirectional Iterator  |
//   |                                    |                              |
//   ↓                                    |                              |
// __advance(..., input_iterator_tag)     |                              |
// while (n--) ++i;                       |                              |
//                                        |                              |
//                                        ↓                              |
//               __advance(..., random_access_iterator_tag)              |
//               i += n;                                                 |
//                                                                       |
//                                                                       ↓
//                                   __advance(..., bidirectional_iterator_tag)
//                                   if (n >= 0)
//                                      while (n--) ++i;
//                                   else
//                                      while (n++) --i;

template <class InputIterator, class Distance>
inline void _advance(InputIterator& i, Distance n, input_iterator_tag) {
    while (n--) ++i;
}

template <class BidirectionalIterator, class Distance>
inline void _advance(BidirectionalIterator& i, Distance n,
                      bidirectional_iterator_tag) {
    if (n >= 0)
        while (n--) ++i;
    else
        while (n++) --i;
}

template <class RandomAccessIterator, class Distance>
inline void _advance(RandomAccessIterator& i, Distance n,
                      random_access_iterator_tag) {
    i += n;
}

template <class InputIterator, class Distance>
inline void advance(InputIterator& i, Distance n) {
    _advance(i, n, iterator_category(i));
}

// 其他操作
// C++11 --> next() prev()


// 一些其他 iterator 的实现
// back_insert_iterator


// front_insert_iterator


// insert_iterator


// reverse_bidirectional_iterator


// reverse_iterator
template <class Iterator>
class reverse_iterator {
public:
	typedef Iterator iterator_type;
	typedef reverse_iterator<Iterator> self;

	typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
	typedef typename iterator_traits<Iterator>::value_type value_type;
	typedef typename iterator_traits<Iterator>::difference_type difference_type;
	typedef typename iterator_traits<Iterator>::pointer pointer;
	typedef typename iterator_traits<Iterator>::reference reference;

	typedef const pointer const_pointer;
	typedef const reference const_reference;

protected:
	Iterator current_;

public:
	constexpr reverse_iterator() = default;
	constexpr explicit reverse_iterator(iterator_type x) : current_(x) {}
	constexpr explicit reverse_iterator(const iterator_type& x) : current_(x) {}
	~reverse_iterator() = default;

	template <class U>
	constexpr reverse_iterator(const reverse_iterator<U>& other)
	    : current_(other.current_) {}
	template <class U>
	constexpr self& operator=(const reverse_iterator<U>& other) {
		if (this == &other)
			return *this;
		
		this->current_ = other.current_;
		return *this;
	}

	constexpr iterator_type base() { return current_; }

	constexpr reference operator*() { return (*current_); }
	constexpr const_reference operator*() const { return (*current_); }
	constexpr pointer operator->() { return &(operator*()); }
	constexpr const_pointer operator->() const { return &(operator*()); }

	constexpr self& operator++() {
		current_--;
		return *this;
	}
	constexpr self operator++(int) {
		self temp = *this;
		current_--;
		return temp;
	}

	constexpr self& operator--() {
		current_++;
		return *this;
	}
	constexpr self operator--(int) {
		self temp = *this;
		current_++;
		return temp;
	}

	constexpr self operator+(difference_type n) const { return self(current_ - n); }
	constexpr self& operator+=(difference_type n) {
		current_ -= n;
		return *this;
	}
	constexpr self operator-(difference_type n) const { return self(current_ + n); }
	constexpr self& operator-=(difference_type n) {
		current_ += n;
		return *this;
	}

	constexpr reference operator[](difference_type n) { return *(*this + n); }
}; // end of reverse_iterator_t

template <class Iterator1, class Iterator2>
constexpr bool operator==(const reverse_iterator<Iterator1>& lhs,
                	   const reverse_iterator<Iterator2>& rhs) {
	return lhs.base() == rhs.base();
}
template <class Iterator1, class Iterator2>
constexpr bool operator!=(const reverse_iterator<Iterator1>& lhs,
                                 const reverse_iterator<Iterator2>& rhs) {
	return !(lhs == rhs);
}

template <class Iterator1, class Iterator2>
constexpr bool operator<(const reverse_iterator<Iterator1>& lhs,
                                const reverse_iterator<Iterator2>& rhs) {
	return lhs.base() < rhs.base();
}
template <class Iterator1, class Iterator2>
constexpr bool operator>(const reverse_iterator<Iterator1>& lhs,
                                const reverse_iterator<Iterator2>& rhs) {
	return lhs.base() > rhs.base();
}
template <class Iterator1, class Iterator2>
constexpr bool operator>=(const reverse_iterator<Iterator1>& lhs,
                                 const reverse_iterator<Iterator2>& rhs) {
	return !(lhs < rhs);
}
template <class Iterator1, class Iterator2>
constexpr bool operator<=(const reverse_iterator<Iterator1>& lhs,
                                 const reverse_iterator<Iterator2>& rhs) {
	return !(lhs > rhs);
}

template <class Iterator1, class Iterator2>
constexpr auto operator-(const reverse_iterator<Iterator1>& lhs,
          const reverse_iterator<Iterator2>& rhs) {
	return lhs.base() - rhs.base();
}
template <class Iterator>
constexpr reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
          const reverse_iterator<Iterator>& rev_it) {
	return rev_it + n;
}

template <class Iterator>
constexpr reverse_iterator<Iterator> make_reverse_iterator(Iterator i) {
	return reverse_iterator<Iterator>(i);
}

// move_iterator


// istream_iterator


// ostream_iterator


MSTL_NAMESPACE_END

#endif