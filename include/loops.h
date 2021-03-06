#ifndef _LOOPS_H_
#define _LOOPS_H_

#include "utils.h"

template <typename T, typename U, typename model> struct vector_evaluator;

template <int unroll, typename Enable = void> struct loop {
  template <typename vector_model, typename scalar_model, typename T1>
  static void execute(T1 expr, const size_t N) {
    size_t i = 0;
    vector_evaluator<T1, size_t, vector_model> root0;

    root0.prepare(expr);
    const size_t size1 = N & (~(1 * vector_model::pack_size - 1));
    for (; i < size1; i += vector_model::pack_size) {
      root0.load(expr, i);
      root0(expr, i);
      root0.store(expr, i);
    }
    vector_evaluator<T1, size_t, scalar_model> root;
    root.prepare(expr);
    for (; i < N; i += scalar_model::pack_size) {
      root.load(expr, i);
      root(expr, i);
      root.store(expr, i);
    }
  }
};

template <typename vector_model, typename scalar_model, int unroll, size_t N,
          typename Enable = void>
struct short_loop {
  template <typename T1> static void execute(T1 expr) {
    loop<unroll>().template execute<vector_model, scalar_model>(expr, N);
  }
};

template <typename vector_model, typename scalar_model, int unroll, size_t N>
struct short_loop<
    vector_model, scalar_model, unroll, N,
    typename std::enable_if<(N < vector_model::pack_size), void>::type> {
  template <typename T1> static void execute(T1 expr) {
    size_t i = 0;
    vector_evaluator<T1, size_t, scalar_model> root;
    root.prepare(expr);
    for (; i < N; i += scalar_model::pack_size) {
      root.load(expr, i);
      root(expr, i);
      root.store(expr, i);
    }
  }
};

template <typename vector_model, typename scalar_model, int unroll, size_t N>
struct short_loop<
    vector_model, scalar_model, unroll, N,
    typename std::enable_if<(N == vector_model::pack_size), void>::type> {
  template <typename T1> static void execute(T1 expr) {
    vector_evaluator<T1, size_t, vector_model> root0;
    root0.prepare(expr);
    root0.load(expr, 0);
    root0(expr, 0);
    root0.store(expr, 0);
  }
};

template <typename vector_model, typename scalar_model, int unroll, size_t N>
struct short_loop<vector_model, scalar_model, unroll, N,
                  typename std::enable_if<(N > vector_model::pack_size &&
                                           N < 2 * vector_model::pack_size),
                                          void>::type> {
  template <typename T1> static void execute(T1 expr) {
    vector_evaluator<T1, size_t, vector_model> root0;
    root0.prepare(expr);
    root0.load(expr, 0);
    root0(expr, 0);
    root0.store(expr, 0);

    size_t i = vector_model::pack_size;
    vector_evaluator<T1, size_t, scalar_model> root;
    root.prepare(expr);
    for (; i < N; i += scalar_model::pack_size) {
      root.load(expr, i);
      root(expr, i);
      root.store(expr, i);
    }
  }
};

template <typename vector_model, typename scalar_model, int unroll, size_t N>
struct short_loop<
    vector_model, scalar_model, unroll, N,
    typename std::enable_if<(N == 2 * vector_model::pack_size), void>::type> {
  template <typename T1> static void execute(T1 expr) {
    vector_evaluator<T1, size_t, vector_model> root0;
    root0.prepare(expr);

    root0.load(expr, 0 * vector_model::pack_size);
    root0(expr, 0 * vector_model::pack_size);
    root0.store(expr, 0 * vector_model::pack_size);

    root0.load(expr, 1 * vector_model::pack_size);
    root0(expr, 1 * vector_model::pack_size);
    root0.store(expr, 1 * vector_model::pack_size);
  }
};

template <typename vector_model, typename scalar_model, int unroll, size_t N>
struct short_loop<vector_model, scalar_model, unroll, N,
                  typename std::enable_if<(N > 2 * vector_model::pack_size &&
                                           N < 3 * vector_model::pack_size),
                                          void>::type> {
  template <typename T1> static void execute(T1 expr) {
    vector_evaluator<T1, size_t, vector_model> root0;
    root0.prepare(expr);

    root0.load(expr, 0 * vector_model::pack_size);
    root0(expr, 0 * vector_model::pack_size);
    root0.store(expr, 0 * vector_model::pack_size);

    root0.load(expr, 1 * vector_model::pack_size);
    root0(expr, 1 * vector_model::pack_size);
    root0.store(expr, 1 * vector_model::pack_size);

    size_t i = 2 * vector_model::pack_size;
    vector_evaluator<T1, size_t, scalar_model> root;
    root.prepare(expr);
    for (; i < N; i += scalar_model::pack_size) {
      root.load(expr, i);
      root(expr, i);
      root.store(expr, i);
    }
  }
};

template <typename vector_model, typename scalar_model, int unroll, size_t N>
struct short_loop<
    vector_model, scalar_model, unroll, N,
    typename std::enable_if<(N == 3 * vector_model::pack_size), void>::type> {
  template <typename T1> static void execute(T1 expr) {
    vector_evaluator<T1, size_t, vector_model> root0;
    root0.prepare(expr);

    root0.load(expr, 0 * vector_model::pack_size);
    root0(expr, 0 * vector_model::pack_size);
    root0.store(expr, 0 * vector_model::pack_size);

    root0.load(expr, 1 * vector_model::pack_size);
    root0(expr, 1 * vector_model::pack_size);
    root0.store(expr, 1 * vector_model::pack_size);

    root0.load(expr, 2 * vector_model::pack_size);
    root0(expr, 2 * vector_model::pack_size);
    root0.store(expr, 2 * vector_model::pack_size);
  }
};

template <typename vector_model, typename scalar_model, int unroll, size_t N>
struct short_loop<vector_model, scalar_model, unroll, N,
                  typename std::enable_if<(N > 3 * vector_model::pack_size &&
                                           N < 4 * vector_model::pack_size),
                                          void>::type> {
  template <typename T1> static void execute(T1 expr) {
    vector_evaluator<T1, size_t, vector_model> root0;
    root0.prepare(expr);

    root0.load(expr, 0 * vector_model::pack_size);
    root0(expr, 0 * vector_model::pack_size);
    root0.store(expr, 0 * vector_model::pack_size);

    root0.load(expr, 1 * vector_model::pack_size);
    root0(expr, 1 * vector_model::pack_size);
    root0.store(expr, 1 * vector_model::pack_size);

    root0.load(expr, 2 * vector_model::pack_size);
    root0(expr, 2 * vector_model::pack_size);
    root0.store(expr, 2 * vector_model::pack_size);

    size_t i = 3 * vector_model::pack_size;
    vector_evaluator<T1, size_t, scalar_model> root;
    root.prepare(expr);
    for (; i < N; i += scalar_model::pack_size) {
      root.load(expr, i);
      root(expr, i);
      root.store(expr, i);
    }
  }
};

template <typename vector_model, typename scalar_model, int unroll, size_t N>
struct short_loop<
    vector_model, scalar_model, unroll, N,
    typename std::enable_if<(N == 4 * vector_model::pack_size), void>::type> {
  template <typename T1> static void execute(T1 expr) {
    vector_evaluator<T1, size_t, vector_model> root0;
    root0.prepare(expr);

    root0.load(expr, 0 * vector_model::pack_size);
    root0(expr, 0 * vector_model::pack_size);
    root0.store(expr, 0 * vector_model::pack_size);

    root0.load(expr, 1 * vector_model::pack_size);
    root0(expr, 1 * vector_model::pack_size);
    root0.store(expr, 1 * vector_model::pack_size);

    root0.load(expr, 2 * vector_model::pack_size);
    root0(expr, 2 * vector_model::pack_size);
    root0.store(expr, 2 * vector_model::pack_size);

    root0.load(expr, 3 * vector_model::pack_size);
    root0(expr, 3 * vector_model::pack_size);
    root0.store(expr, 3 * vector_model::pack_size);
  }
};

template <int unroll>
struct loop<unroll,
            typename std::enable_if<(unroll >= 2 && unroll < 4), void>::type> {
  template <typename vector_model, typename scalar_model, typename T1>
  static void execute(T1 expr, const size_t N) {
    size_t i = 0;
    vector_evaluator<T1, size_t, vector_model> root0;
    vector_evaluator<T1, size_t, vector_model> root1;

    root0.prepare(expr);
    root1.prepare(expr);

    const size_t size8 = N & (~(8 * vector_model::pack_size - 1));
    for (; i < size8; i += 8 * vector_model::pack_size) {
      root0.load(expr, i + 0 * vector_model::pack_size);
      root1.load(expr, i + 1 * vector_model::pack_size);

      root0(expr, i + 0 * vector_model::pack_size);
      root1(expr, i + 1 * vector_model::pack_size);

      root0.store(expr, i + 0 * vector_model::pack_size);
      root1.store(expr, i + 1 * vector_model::pack_size);

      root0.load(expr, i + 2 * vector_model::pack_size);
      root1.load(expr, i + 3 * vector_model::pack_size);

      root0(expr, i + 2 * vector_model::pack_size);
      root1(expr, i + 3 * vector_model::pack_size);

      root0.store(expr, i + 2 * vector_model::pack_size);
      root1.store(expr, i + 3 * vector_model::pack_size);

      root0.load(expr, i + 4 * vector_model::pack_size);
      root1.load(expr, i + 5 * vector_model::pack_size);

      root0(expr, i + 4 * vector_model::pack_size);
      root1(expr, i + 5 * vector_model::pack_size);

      root0.store(expr, i + 4 * vector_model::pack_size);
      root1.store(expr, i + 5 * vector_model::pack_size);

      root0.load(expr, i + 6 * vector_model::pack_size);
      root1.load(expr, i + 7 * vector_model::pack_size);

      root0(expr, i + 6 * vector_model::pack_size);
      root1(expr, i + 7 * vector_model::pack_size);

      root0.store(expr, i + 6 * vector_model::pack_size);
      root1.store(expr, i + 7 * vector_model::pack_size);
    }
    const size_t size2 = N & (~(2 * vector_model::pack_size - 1));
    for (; i < size2; i += 2 * vector_model::pack_size) {
      root0.load(expr, i + 0 * vector_model::pack_size);
      root1.load(expr, i + 1 * vector_model::pack_size);

      root0(expr, i + 0 * vector_model::pack_size);
      root1(expr, i + 1 * vector_model::pack_size);

      root0.store(expr, i + 0 * vector_model::pack_size);
      root1.store(expr, i + 1 * vector_model::pack_size);
    }
    const size_t size1 = N & (~(1 * vector_model::pack_size - 1));
    for (; i < size1; i += 1 * vector_model::pack_size) {
      root0.load(expr, i + 0 * vector_model::pack_size);
      root0(expr, i + 0 * vector_model::pack_size);
      root0.store(expr, i + 0 * vector_model::pack_size);
    }
    vector_evaluator<T1, size_t, scalar_model> root;
    root.prepare(expr);
    for (; i < N; i += scalar_model::pack_size) {
      root.load(expr, i);
      root(expr, i);
      root.store(expr, i);
    }
  }
};

template <int unroll>
struct loop<unroll,
            typename std::enable_if<(unroll >= 4 && unroll < 8), void>::type> {
  template <typename vector_model, typename scalar_model, typename T1>
  static void execute(T1 expr, const size_t N) {
    size_t i = 0;
    vector_evaluator<T1, size_t, vector_model> root0;
    vector_evaluator<T1, size_t, vector_model> root1;
    vector_evaluator<T1, size_t, vector_model> root2;
    vector_evaluator<T1, size_t, vector_model> root3;

    root0.prepare(expr);
    root1.prepare(expr);
    root2.prepare(expr);
    root3.prepare(expr);

    const size_t size16 = N & (~(16 * vector_model::pack_size - 1));
    for (; i < size16; i += 16 * vector_model::pack_size) {
      root0.load(expr, i + 0 * vector_model::pack_size);
      root1.load(expr, i + 1 * vector_model::pack_size);
      root2.load(expr, i + 2 * vector_model::pack_size);
      root3.load(expr, i + 3 * vector_model::pack_size);

      root0(expr, i + 0 * vector_model::pack_size);
      root1(expr, i + 1 * vector_model::pack_size);
      root2(expr, i + 2 * vector_model::pack_size);
      root3(expr, i + 3 * vector_model::pack_size);

      root0.store(expr, i + 0 * vector_model::pack_size);
      root1.store(expr, i + 1 * vector_model::pack_size);
      root2.store(expr, i + 2 * vector_model::pack_size);
      root3.store(expr, i + 3 * vector_model::pack_size);

      root0.load(expr, i + 4 * vector_model::pack_size);
      root1.load(expr, i + 5 * vector_model::pack_size);
      root2.load(expr, i + 6 * vector_model::pack_size);
      root3.load(expr, i + 7 * vector_model::pack_size);

      root0(expr, i + 4 * vector_model::pack_size);
      root1(expr, i + 5 * vector_model::pack_size);
      root2(expr, i + 6 * vector_model::pack_size);
      root3(expr, i + 7 * vector_model::pack_size);

      root0.store(expr, i + 4 * vector_model::pack_size);
      root1.store(expr, i + 5 * vector_model::pack_size);
      root2.store(expr, i + 6 * vector_model::pack_size);
      root3.store(expr, i + 7 * vector_model::pack_size);

      root0.load(expr, i + 8 * vector_model::pack_size);
      root1.load(expr, i + 9 * vector_model::pack_size);
      root2.load(expr, i + 10 * vector_model::pack_size);
      root3.load(expr, i + 11 * vector_model::pack_size);

      root0(expr, i + 8 * vector_model::pack_size);
      root1(expr, i + 9 * vector_model::pack_size);
      root2(expr, i + 10 * vector_model::pack_size);
      root3(expr, i + 11 * vector_model::pack_size);

      root0.store(expr, i + 8 * vector_model::pack_size);
      root1.store(expr, i + 9 * vector_model::pack_size);
      root2.store(expr, i + 10 * vector_model::pack_size);
      root3.store(expr, i + 11 * vector_model::pack_size);

      root0.load(expr, i + 12 * vector_model::pack_size);
      root1.load(expr, i + 13 * vector_model::pack_size);
      root2.load(expr, i + 14 * vector_model::pack_size);
      root3.load(expr, i + 15 * vector_model::pack_size);

      root0(expr, i + 12 * vector_model::pack_size);
      root1(expr, i + 13 * vector_model::pack_size);
      root2(expr, i + 14 * vector_model::pack_size);
      root3(expr, i + 15 * vector_model::pack_size);

      root0.store(expr, i + 12 * vector_model::pack_size);
      root1.store(expr, i + 13 * vector_model::pack_size);
      root2.store(expr, i + 14 * vector_model::pack_size);
      root3.store(expr, i + 15 * vector_model::pack_size);
    }
    const size_t size4 = N & (~(4 * vector_model::pack_size - 1));
    for (; i < size4; i += 4 * vector_model::pack_size) {
      root0.load(expr, i + 0 * vector_model::pack_size);
      root1.load(expr, i + 1 * vector_model::pack_size);
      root2.load(expr, i + 2 * vector_model::pack_size);
      root3.load(expr, i + 3 * vector_model::pack_size);

      root0(expr, i + 0 * vector_model::pack_size);
      root1(expr, i + 1 * vector_model::pack_size);
      root2(expr, i + 2 * vector_model::pack_size);
      root3(expr, i + 3 * vector_model::pack_size);

      root0.store(expr, i + 0 * vector_model::pack_size);
      root1.store(expr, i + 1 * vector_model::pack_size);
      root2.store(expr, i + 2 * vector_model::pack_size);
      root3.store(expr, i + 3 * vector_model::pack_size);
    }
    const size_t size1 = N & (~(1 * vector_model::pack_size - 1));
    for (; i < size1; i += 1 * vector_model::pack_size) {
      root0.load(expr, i + 0 * vector_model::pack_size);
      root0(expr, i + 0 * vector_model::pack_size);
      root0.store(expr, i + 0 * vector_model::pack_size);
    }
    vector_evaluator<T1, size_t, scalar_model> root;
    root.prepare(expr);
    for (; i < N; i += scalar_model::pack_size) {
      root.load(expr, i);
      root(expr, i);
      root.store(expr, i);
    }
  }
};

template <int unroll>
struct loop<unroll, typename std::enable_if<(unroll >= 8), void>::type> {
  template <typename vector_model, typename scalar_model, typename T1>
  static void execute(T1 expr, const size_t N) {
    size_t i = 0;
    vector_evaluator<T1, size_t, vector_model> root0;
    vector_evaluator<T1, size_t, vector_model> root1;
    vector_evaluator<T1, size_t, vector_model> root2;
    vector_evaluator<T1, size_t, vector_model> root3;
    vector_evaluator<T1, size_t, vector_model> root4;
    vector_evaluator<T1, size_t, vector_model> root5;
    vector_evaluator<T1, size_t, vector_model> root6;
    vector_evaluator<T1, size_t, vector_model> root7;

    root0.prepare(expr);
    root1.prepare(expr);
    root2.prepare(expr);
    root3.prepare(expr);
    root4.prepare(expr);
    root5.prepare(expr);
    root6.prepare(expr);
    root7.prepare(expr);

    const size_t size16 = N & (~(16 * vector_model::pack_size - 1));
    for (; i < size16; i += 16 * vector_model::pack_size) {
      root0.load(expr, i + 0 * vector_model::pack_size);
      root1.load(expr, i + 1 * vector_model::pack_size);
      root2.load(expr, i + 2 * vector_model::pack_size);
      root3.load(expr, i + 3 * vector_model::pack_size);

      root4.load(expr, i + 4 * vector_model::pack_size);
      root5.load(expr, i + 5 * vector_model::pack_size);
      root6.load(expr, i + 6 * vector_model::pack_size);
      root7.load(expr, i + 7 * vector_model::pack_size);

      root0(expr, i + 0 * vector_model::pack_size);
      root1(expr, i + 1 * vector_model::pack_size);
      root2(expr, i + 2 * vector_model::pack_size);
      root3(expr, i + 3 * vector_model::pack_size);

      root4(expr, i + 4 * vector_model::pack_size);
      root5(expr, i + 5 * vector_model::pack_size);
      root6(expr, i + 6 * vector_model::pack_size);
      root7(expr, i + 7 * vector_model::pack_size);

      root0.store(expr, i + 0 * vector_model::pack_size);
      root1.store(expr, i + 1 * vector_model::pack_size);
      root2.store(expr, i + 2 * vector_model::pack_size);
      root3.store(expr, i + 3 * vector_model::pack_size);

      root4.store(expr, i + 4 * vector_model::pack_size);
      root5.store(expr, i + 5 * vector_model::pack_size);
      root6.store(expr, i + 6 * vector_model::pack_size);
      root7.store(expr, i + 7 * vector_model::pack_size);

      root0.load(expr, i + 8 * vector_model::pack_size);
      root1.load(expr, i + 9 * vector_model::pack_size);
      root2.load(expr, i + 10 * vector_model::pack_size);
      root3.load(expr, i + 11 * vector_model::pack_size);

      root4.load(expr, i + 12 * vector_model::pack_size);
      root5.load(expr, i + 13 * vector_model::pack_size);
      root6.load(expr, i + 14 * vector_model::pack_size);
      root7.load(expr, i + 15 * vector_model::pack_size);

      root0(expr, i + 8 * vector_model::pack_size);
      root1(expr, i + 9 * vector_model::pack_size);
      root2(expr, i + 10 * vector_model::pack_size);
      root3(expr, i + 11 * vector_model::pack_size);

      root4(expr, i + 12 * vector_model::pack_size);
      root5(expr, i + 13 * vector_model::pack_size);
      root6(expr, i + 14 * vector_model::pack_size);
      root7(expr, i + 15 * vector_model::pack_size);

      root0.store(expr, i + 8 * vector_model::pack_size);
      root1.store(expr, i + 9 * vector_model::pack_size);
      root2.store(expr, i + 10 * vector_model::pack_size);
      root3.store(expr, i + 11 * vector_model::pack_size);

      root4.store(expr, i + 12 * vector_model::pack_size);
      root5.store(expr, i + 13 * vector_model::pack_size);
      root6.store(expr, i + 14 * vector_model::pack_size);
      root7.store(expr, i + 15 * vector_model::pack_size);
    }
    const size_t size4 = N & (~(4 * vector_model::pack_size - 1));
    for (; i < size4; i += 4 * vector_model::pack_size) {
      root0.load(expr, i + 0 * vector_model::pack_size);
      root1.load(expr, i + 1 * vector_model::pack_size);
      root2.load(expr, i + 2 * vector_model::pack_size);
      root3.load(expr, i + 3 * vector_model::pack_size);

      root0(expr, i + 0 * vector_model::pack_size);
      root1(expr, i + 1 * vector_model::pack_size);
      root2(expr, i + 2 * vector_model::pack_size);
      root3(expr, i + 3 * vector_model::pack_size);

      root0.store(expr, i + 0 * vector_model::pack_size);
      root1.store(expr, i + 1 * vector_model::pack_size);
      root2.store(expr, i + 2 * vector_model::pack_size);
      root3.store(expr, i + 3 * vector_model::pack_size);
    }
    const size_t size1 = N & (~(1 * vector_model::pack_size - 1));
    for (; i < size1; i += 1 * vector_model::pack_size) {
      root0.load(expr, i + 0 * vector_model::pack_size);
      root0(expr, i + 0 * vector_model::pack_size);
      root0.store(expr, i + 0 * vector_model::pack_size);
    }
    vector_evaluator<T1, size_t, scalar_model> root;
    root.prepare(expr);
    for (; i < N; i += scalar_model::pack_size) {
      root.load(expr, i);
      root(expr, i);
      root.store(expr, i);
    }
  }
};

#endif // _LOOPS_H_
