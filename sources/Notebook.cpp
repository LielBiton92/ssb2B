#include "Notebook.hpp"
#include <iostream>
#include "stdexcept"
#include "vector"
#include "string"
using namespace std;
using namespace ariel;
const int col_limit = 100;
 unsigned int i=0;
 const int MINCHAR = 32;
 const int MAXCHAR = 126;
 const int lim_col = 99;

 void ariel::check_t(const unsigned int col ,const unsigned int tw ){
         if (col + tw  > col_limit){
               throw std::invalid_argument("cannot reading/writing after col num 100 "); 
         }
 }

 void ariel::check_t2(int page , int row , int col){
         if (page < 0 or row < 0 or col < 0){
                 throw::out_of_range("page row and col cannot be negative");
         }
                         if(col >lim_col){
                throw::out_of_range("max col is 100");
        }
 }

// void ariel::Notebook::check_throws(const  int page ,const  int row ,const  int col ,const Direction state ,const  int numtocheck){
//         if(this->check_dirty(page , row , col , state , numtocheck)){
//                 throw std::invalid_argument("");
//         }
//         if (state ==Direction::Horizontal){
//                 if(col+numtocheck > col_limit){
//                 throw std::invalid_argument("@@@@@@@@@");
//         }
//         }
// }

void ariel::Notebook::check_pages_size(const  int page ){
        if(this->mynotebook.size()<=page){
                this->mynotebook.resize((unsigned int)page+1);
        }
}

bool ariel::Notebook::check_dirty(const  int page ,const  int row ,const  int col ,const Direction state ,const  int numtocheck){
        bool ans = this->mynotebook.at((unsigned int)page).check_dirty((unsigned int)row , (unsigned int)col , state , (unsigned int)numtocheck);
        return ans;  
}

void ariel::Notebook::write(const  int page ,const  int row ,const  int col ,const Direction state ,const std::string &towrite){
        check_t2(page , row , col);


        if(state==Direction::Horizontal){
        check_t((unsigned int)col , towrite.size());
        }
        check_pages_size(page);
        this->mynotebook[(unsigned int)page].write((unsigned int)row , (unsigned int)col , state , towrite);
        

}

string ariel::Notebook::read(const  int page ,const   int row ,const   int col ,const Direction state ,const  int num){
        check_t2(page , row , col);

        if (state == Direction::Horizontal){
                check_t((unsigned int)col , (unsigned int)num);
        }
        check_pages_size(page);
      //  this->check_throws(page , row , col , state , num);

        return this->mynotebook[(unsigned int)page].read((unsigned int)row , (unsigned int)col , state , (unsigned int)num);

}

void ariel::Notebook::erase(const  int page ,const   int  row ,const   int col ,const Direction state ,const  int num){
        check_t2(page , row , col);


                if (state ==Direction::Horizontal){
                        check_t((unsigned int)col , (unsigned int)num);
        }
        check_pages_size(page);
        this->mynotebook[(unsigned int)page].erase((unsigned int)row , (unsigned int)col , state , (unsigned int)num);
}

void ariel::Notebook::show(  int page){
        check_t2(page , 0 ,0);
        check_pages_size(page);
        this->mynotebook[(unsigned int)page].show_page();
}


ariel::Row::Row(){
        for(unsigned int j = 0 ; j < col_limit ; j++){
                this->myrow.push_back('_');
        }
}
// ariel::Row::~Row(){
//         delete[] myrow;
// }

void ariel::Row::write(const unsigned int pos ,const string &tw){
        for(unsigned int i = 0 ; i <tw.size();i++){
                if(tw[i]=='~' or tw[i]<MINCHAR or tw[i]>MAXCHAR){
                        throw::invalid_argument("----");
                }
        }
        for (i = 0;i< tw.size();i++){
                this->myrow[pos+i]=tw[i];
        }
}

void ariel::Row::writechar(const unsigned int pos ,const char tw){
        if(tw=='~' or tw<MINCHAR or tw>MAXCHAR){
                        throw::invalid_argument("----");
                }
               this->myrow[pos]=tw;   
}

void ariel::Row::erase(const unsigned int pos ,const unsigned int len){
        for (i = 0 ; i< len;i++){
                this->myrow[pos+i]='~';
        }
}

string ariel::Row::read(const unsigned int pos ,const  unsigned int len){
        string ans;
        
        for(i = 0 ; i< len ; i++){
                ans += this->myrow[pos+i];
        }
        return ans;

}





char ariel::Row::readchar(const unsigned int pos){
        return this->myrow[pos];
}

bool ariel::Row::check_dirty(const unsigned int pos ,const unsigned int numtocheck){
        for(i = 0 ; i < numtocheck ; i++){
                if(this->myrow[pos+i]!='_'){
                        return true ;
                }
                
        }
        return false;
}
bool ariel::Row::check_dirty_char(const unsigned int pos ){
        bool ans = false;
        if(this->myrow[pos]!='_'){
                ans = true;
        }
        return ans;
}

void ariel::Row::show_row(){
         for(unsigned int i = 0 ; i < this->myrow.size(); i++){
                 cout << myrow[i] ;
         }
         cout << endl;
}




void ariel::Page::check_size_rows(const unsigned int row){
        if (this->mypage.size()<=row){
                this->mypage.resize(row+1);       
        }
}


void ariel::Page::check_size_cols(const unsigned int row ,const string &tw){
        if (this->mypage.size()<=row + tw.size()){
                this->mypage.resize(row+tw.size());

        }
}
void ariel::Page::check_size_cols_toerase(const unsigned int row ,const unsigned int  numtodel){
        if(this->mypage.size()<=row+numtodel){
                this->mypage.resize(row+numtodel);
        }

}

void ariel::Page::write(const unsigned int row ,const  unsigned int pos ,const Direction state ,const std::string &tw){
        check_size_rows(row);
        check_size_cols(row , tw);
        if(check_dirty(row , pos , state , tw.size())){
                throw std::invalid_argument("vvvvv");
        }

        if(state == Direction::Horizontal){
                this->mypage[row].write(pos,tw);
}

        else if(state == Direction::Vertical){
                 unsigned int j = 0;
                 unsigned int k  = row;
                while(k < row+tw.size()){
                        this->mypage[row+j].writechar(pos ,tw.at(j));
                
                        k+=1;
                        j+=1;
                }
        

        }
}

void ariel::Page::erase(const unsigned int row ,const  unsigned int pos ,const Direction state ,const unsigned int numtodel){

        
        if (state == Direction::Horizontal){
                check_size_rows(row);
                this->mypage[row].erase(pos , numtodel);
        }
        else if (state == Direction::Vertical){
                check_size_cols_toerase(row , numtodel);
                 unsigned int j = 0 ;
                 unsigned int k = row ;
                while(k < row+numtodel){
                        this->mypage[row+j].erase(pos , 1);
                        k+=1;
                        j+=1;
                }
                
        }
}

string ariel::Page::read(const unsigned int row ,const  unsigned int pos ,const Direction state ,const  unsigned int numtoread){
        check_size_rows(row);
        check_size_cols_toerase(row , numtoread);
        string res;
        
        if (state == Direction::Horizontal){
                res = this->mypage[row].read(pos , numtoread);
        }
        else if(state == Direction::Vertical){
                if(this->mypage.size()<row+numtoread){
                        this->mypage.resize(row+numtoread);
                }
                 unsigned int j = 0 ; 
                i = row ; 
                while (i < row + numtoread){
                        res += this->mypage[row+j].readchar(pos);

                        i+= 1;
                        j+= 1;
                        
                        
                }
        }
        return res;
}

bool ariel::Page::check_dirty(const unsigned int row ,const unsigned int pos ,const Direction state ,const unsigned int numtocheck){
        bool ans=false ;
        bool final_ans = false; 
        if( state == Direction::Horizontal){
              ans =   this->mypage[row].check_dirty(pos , numtocheck);
              
}

        else if(state == Direction::Vertical){
                check_size_cols_toerase(row , numtocheck);
                unsigned int j = 0;
                unsigned int k  = row;
                while(k < row+numtocheck){
                   ans = this->mypage[row+j].check_dirty_char(pos);
                   if(ans){
                           final_ans = true;
                   }
                        
        
                        k+=1;
                        j+=1;
                }
        

        }
        if (final_ans){
                ans = true;
        }
        return ans;
        
}


void ariel::Page::show_page(){
        for(i = 0 ; i < this->mypage.size(); i++){
                this->mypage.at(i).show_row();
                
        }
        
}











        
        
        


