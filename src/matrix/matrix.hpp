// Copyright 2024 stranger

#ifndef _A2_SIMPLE_NAVIGATOR_SRC_MATRIX_MATRIX_HPP_
#define _A2_SIMPLE_NAVIGATOR_SRC_MATRIX_MATRIX_HPP_

namespace s21 {

template <typename T>
class Matrix {
 public:
  /**
   * @brief Default Matrix class constructor.
   */
  Matrix() : rows_(0), columns_(0), capacity_(0), data_(nullptr) {}

  /**
   * @brief Class constructor with size parameter.
   */
  Matrix(const std::size_t size, const T& value = T{})
      : rows_(size),
        columns_(size),
        capacity_(size * size),
        data_(capacity_ != 0 ? new T[capacity_]{} : nullptr) {
    std::fill(data_, data_ + capacity_, value);
  }

  /**
   * @brief Class constructor with rows and columns parameters.
   */
  Matrix(const std::size_t rows, const std::size_t columns,
         const T& value = T{})
      : rows_(rows),
        columns_(columns),
        capacity_(rows_ * columns_),
        data_(capacity_ != 0 ? new T[capacity_]{} : nullptr) {
    std::fill(data_, data_ + capacity_, value);
  }

  /**
   * @brief Class constructor with initializer list.
   */
  Matrix(const std::size_t rows, const std::size_t columns,
         const std::initializer_list<T>& list) {
    if (rows * columns != list.size()) return;

    rows_ = rows;
    columns_ = columns;
    capacity_ = rows_ * columns_;

    data_ = new T[capacity_]{};

    unsigned int index = 0;

    for (auto item : list) {
      data_[index] = item;

      ++index;
    }
  }

  /**
   * @brief Copy contructor.
   */
  Matrix(const Matrix& other) {
    rows_ = other.rows_;
    columns_ = other.columns_;
    capacity_ = other.capacity_;

    data_ = new T[capacity_]{};

    std::copy(other.data_, other.data_ + capacity_, data_);
  }

  /**
   * @brief Move constructor.
   */
  Matrix(Matrix&& other) noexcept : Matrix() {
    std::swap(rows_, other.rows_);
    std::swap(columns_, other.columns_);
    std::swap(capacity_, other.capacity_);
    std::swap(data_, other.data_);
  }

  /**
   * @brief Destructor of the Matrix class.
   */
  ~Matrix() {
    if (data_ == nullptr) return;

    delete[] data_;
  }

  /**
   * @brief Copying assignment operator.
   * @param other Matrix reference parameter.
   */
  Matrix& operator=(const Matrix& other) {
    if (this == &other) return *this;

    rows_ = other.rows_;
    columns_ = other.columns_;
    capacity_ = other.capacity_;

    if (data_ != nullptr) delete[] data_;

    data_ = new T[capacity_]{};

    std::copy(other.data_, other.data_ + capacity_, data_);

    return *this;
  }

  /**
   * @brief Rvalue assignment operator.
   * @param other Rvalue parameter.
   */
  Matrix& operator=(Matrix&& other) noexcept {
    if (this == &other) return *this;

    if (data_ != nullptr) delete[] data_;

    rows_ = other.rows_;
    columns_ = other.columns_;
    capacity_ = other.capacity_;
    data_ = other.data_;

    other.rows_ = 0;
    other.columns_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;

    return *this;
  }

  /**
   * @brief compares objects of Matrix class.
   */
  bool operator==(const Matrix& other) const {
    if (rows_ != other.rows_ || columns_ != other.columns_) return false;

    return std::equal(other.begin(), other.end(), data_);
  }

  /**
   * @brief Provides access to matrix without segmentation fault.
   * @param row Row element index.
   * @param col Column element index.
   * @return Element reference from matrix.
   */
  [[nodiscard]] T& operator()(const std::size_t row, const std::size_t col) {
    if (row < rows_ && col < columns_) return data_[row * columns_ + col];

    static T default_value{};

    return default_value;
  }

  /**
   * @brief Provides access to matrix without segmentation fault.
   * @param row Row element index.
   * @param col Column element index.
   * @return Value stored in the matrix.
   */
  const T& operator()(const std::size_t row, const std::size_t col) const {
    if (row < rows_ && col < columns_) return data_[row * columns_ + col];

    const static T default_value{0};

    return default_value;
  }

  /**
   * @brief Provides access to graph without segmentation fault.
   * @param pos Element index.
   * @return Element reference from matrix.
   */
  [[nodiscard]] T& operator()(const std::size_t pos) {
    if (pos < capacity_) return data_[pos];

    static T default_value{};

    return default_value;
  }

  /**
   * @brief Provides access to graph without segmentation fault.
   * @param pos Element index.
   * @return Value stored in the graph.
   */
  const T& operator()(const std::size_t pos) const {
    if (pos < capacity_) return data_[pos];

    const static T default_value{};

    return default_value;
  }

  /**
   * @brief Returns the number of matrix rows.
   */
  virtual std::size_t rows() const { return rows_; }

  /**
   * @brief Returns the number of matrix columns.
   */
  virtual std::size_t columns() const { return columns_; }

  /**
   * @brief Returns the number of matrix capacity.
   */
  virtual std::size_t capacity() const { return capacity_; }

  /**
   * @brief Returns a first pointer from the matrix.
   */
  [[nodiscard]] T* begin() { return data_; }

  /**
   * @brief Returns a constant first pointer from the matrix.
   */
  const T* begin() const { return data_; }

  /**
   * @brief Returns a last pointer from the matrix.
   */
  [[nodiscard]] T* end() { return data_ + capacity_; }

  /**
   * @brief Returns a constant last pointer from the matrix.
   */
  const T* end() const { return data_ + capacity_; }

 private:
  std::size_t rows_;
  std::size_t columns_;
  std::size_t capacity_;

  T* data_;
};

}  // namespace s21

#endif  // _A2_SIMPLE_NAVIGATOR_SRC_MATRIX_MATRIX_HPP_
