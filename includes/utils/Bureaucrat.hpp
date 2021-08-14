//
// Created by Federico François on 25/06/21.
//

#ifndef CPP05_BUREAUCRAT_HPP
#define CPP05_BUREAUCRAT_HPP

#include <iostream>

class Bureaucrat {
	std::string			name;
	unsigned int		grade;
public:
	Bureaucrat() {};
	Bureaucrat(unsigned int grade): name("Bureaucrat"), grade(grade) {}
	~Bureaucrat() {}
	std::string getName() const {
		return name;
	}
	unsigned int getGrade() const {
		return grade;
	}
	friend
	bool operator== (const Bureaucrat lhs, const Bureaucrat rhs) { return lhs.getGrade() == rhs.getGrade(); }
	friend
	bool operator>  (const Bureaucrat lhs, const Bureaucrat rhs) { return lhs.getGrade() > rhs.getGrade(); }
	friend
	bool operator!= (const Bureaucrat& lhs, const Bureaucrat& rhs) {return !(lhs == rhs);}
	friend
	bool operator<  (const Bureaucrat& lhs, const Bureaucrat& rhs) {return !(lhs > rhs || lhs == rhs);}
	friend
	bool operator<= (const Bureaucrat& lhs, const Bureaucrat& rhs) {return !(lhs > rhs);}
	friend
	bool operator>= (const Bureaucrat& lhs, const Bureaucrat& rhs) {return !(lhs < rhs);}
};


std::ostream& operator<<(std::ostream& os, const Bureaucrat& bureaucrat){
	os <<  bureaucrat.getName() << ", " << bureaucrat.getGrade() << std::endl;
	return os;
}

#endif //CPP05_BUREAUCRAT_HPP
