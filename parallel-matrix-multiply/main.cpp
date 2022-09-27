#include <cmath>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
class Matrix{

  private:
  
  void parallel_worker(Matrix *res, Matrix *B , std::size_t start, std::size_t end){
   for(std::size_t i = start; i<end; i++ ){
      for(std::size_t j=0; j<B->num_cols;j++){
        res->data[i][j] = 0;
        for(std::size_t k = 0; k<this->num_cols; k++){
          res->data[i][j] += this->data[i][k]*B->data[k][j];
        }
      }
    }   
  }
  public:
  const std::size_t num_cols;
  const std::size_t num_rows;
  std::vector<std::vector<long>> data;

  Matrix(const std::size_t num_rows, const std::size_t num_cols):num_rows{num_rows}, num_cols{num_cols}{
    for(std::size_t i=0; i<num_rows; i++){
      std::vector<long> row(num_cols);
      data.emplace_back(row);
    }
  };

  Matrix(std::initializer_list<std::initializer_list<long>> data): num_cols{data.begin()->size()}, num_rows{data.size()}{
    for(const auto row : data){
     this->data.emplace_back(row); 
    }
  }

  // A = M x N 
  // B = N x O 
  // A x B = C
  // C = M x O
  Matrix multiply(const Matrix & other)const{
    if(num_cols != other.num_rows){
      throw new std::string{"Cannot multiply matrices: Number of columns of this matrix is not equal the number rows of the input matrix "};
    }
     Matrix res(this->num_rows, other.num_cols);
    std::cout<< std::endl;
    
    for(std::size_t i=0; i<num_rows; i++){
      for(std::size_t j=0; j<other.num_cols; j++){
        res.data[i][j]=0;
        for(std::size_t k=0; k<num_cols; k++){
          res.data[i][j] += (data[i][k]*other.data[k][j]); 
        }
      }
    }
    return res;
  }

  Matrix multiply_parallel(Matrix other){
    if(num_cols != other.num_rows){
      throw new std::string{"Cannot multiply matrices: Number of columns of this matrix is not equal the number rows of the input matrix "};
    }
    Matrix res(num_rows, other.num_cols);
    std::size_t matrix_chunk_size = std::ceil(((float) num_rows/std::thread::hardware_concurrency()));  
    std::vector<std::thread> workers(std::thread::hardware_concurrency());

    //assign something to each worker
    for(std::size_t i=0; i<workers.size(); i++){
      auto start_row_index = std::min(i*matrix_chunk_size, num_rows);
      auto end_row_index = std::min((i+1)*matrix_chunk_size, num_rows);
      workers[i]= std::thread(&Matrix::parallel_worker, this, &res,  &other, start_row_index, end_row_index);
    }

    for(auto& worker: workers){
      worker.join();
    }

    return res;
  }
  
};


int main(int argc, char* argv[]){
  Matrix mat = {{1,2,3}, {4,5,6}, {7,8,9}};
  Matrix identity_mat = {{1,0,0}, {0,1,0}, {1,0,1}};
  for(auto row: mat.data){
    for (auto cell: row){
      std::cout<<cell<<" ";
    }
    std::cout<<std::endl;
  }

  std::cout<<mat.num_rows<<" x "<< mat.num_cols<<std::endl;
  std::cout<<std::endl; 
  auto C = mat.multiply_parallel(identity_mat);

  for(auto row: C.data){
    for (auto cell: row){
      std::cout<<cell<<" ";
    }
    std::cout<<std::endl;
  }


  std::cout<<C.num_rows<<" x "<< C.num_cols<<std::endl;
}
