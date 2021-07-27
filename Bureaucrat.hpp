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
	Bureaucrat(std::string name, unsigned grade){
		this->name = name;
		this->grade = grade;
	}
	~Bureaucrat() {
		std::cout << "destructor" << std::endl;
	}
	std::string getName() const {
		return name;
	}
	unsigned int getGrade() const {
		return grade;
	}

};

std::ostream& operator<<(std::ostream& os, const Bureaucrat& bureaucrat){
	os <<  bureaucrat.getName() << ", " << bureaucrat.getGrade() << std::endl;
	return os;
}

#endif //CPP05_BUREAUCRAT_HPP
