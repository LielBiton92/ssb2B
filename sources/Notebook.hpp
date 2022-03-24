#include "Direction.hpp"

using ariel::Direction;
const  int  limit = 100;

#include <string>
#include "vector"
using namespace std;
namespace ariel{
        void check_t(unsigned int col , unsigned int tw);
class Notebook;
class Page;
class Row;

class Notebook{
        private:
                 vector <Page> mynotebook;
 
        public:

          void check_pages_size(const unsigned int page);

          void write(const unsigned int page ,const  unsigned int row ,const  unsigned int col ,const Direction state ,const  std::string &towrite);

          std::string read(const unsigned int page ,const  unsigned int row ,const  unsigned int col ,const ariel::Direction state ,const unsigned int  );

          void erase(const unsigned int page ,const  unsigned int  row ,const  unsigned int col ,const Direction state ,const unsigned int num);

          bool check_dirty(const unsigned int page ,const unsigned int row ,const unsigned int col ,const Direction state ,const unsigned int numtocheck);

          void show(const unsigned int page);

          void check_throws(unsigned int page , unsigned int row , unsigned int col ,Direction state , unsigned int numtocheck);




};


class Page{
        protected:
                vector <Row> mypage;

        public:
        // ~page();
        void check_size_rows(const unsigned int row);
        string print();
        void check_size_cols_toerase(const unsigned int row ,const unsigned int numtodel);
        void check_size_cols(const unsigned int row,  std::string const &tw);
        void write(const unsigned int row ,const unsigned int pos ,const Direction state ,const std::string &tw);
        void erase( unsigned int row ,  unsigned int pos , Direction state ,  unsigned int numtodel);
        void show_page();
        bool check_dirty(const unsigned int row ,const unsigned int pos ,const Direction state ,const unsigned int numtocheck);
        std::string read(const unsigned int row ,const  unsigned int pos ,const Direction state ,const  unsigned int numtoread);
        friend void getvec();


};

class Row{
        protected:
                vector <char> myrow;
                

        public:
                Row();
                // ~Row(); 
                void write(const unsigned int pos ,const std::string &tw );
                void erase(const unsigned int pos ,const  unsigned int len);
                char readchar(const unsigned int pos);
                std::string read(const unsigned int pos ,const unsigned int len);
                void writechar(const unsigned int pos ,const char tw);
                bool check_dirty(const unsigned int pos ,const unsigned int numtocheck);
                bool check_dirty_char(const unsigned int pos );
                void show_row();
        
};







}
