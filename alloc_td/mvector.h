#ifndef MVECTOR_H
#define MVECTOR_H

template<class T>
class melement {
public:
	melement * prev;
	melement * next;
	size_t bloc_s;
	long magic_number;
};

template<class T>
class mvector {
	melement * f;
}

#endif