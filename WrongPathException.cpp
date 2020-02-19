
#include <exception>
/**
 * \brief exception thrown when an specified path doesn't
 * lead to any file.
 */
class WrongPathException: public std::exception {

public:

    const char* what() const throw()
    {
        return "Wrong path entered. Not such file exists.";
    }

};
