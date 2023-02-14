#pragma once
#include <bits/stdc++.h>
/// @brief
/// 配列の新規メモリ割当のコストを無くし、全要素の演算を定義したデータ構造
/// @tparam SZ 配列の長さ
template <class T, int SZ> class CirculatedArr {
  private:
    /// @brief 次の要素を保存する場所のidx
    int idx_ = 0;
    /// @brief 使い回す固定長配列
    std::array<T, SZ> data_;

    bool is_over = false;

  public:
    CirculatedArr() {}
    /// @brief 指定された要素で配列を埋める
    /// @param t 
    CirculatedArr(T t) { data_.fill(t); }
    auto begin() { return data_.begin(); }
    auto end() {
        return data_.begin() + std::min(idx_ + (is_over ? SZ : 0), SZ);
    }

    inline void Reset() {
        idx_ = 0;
        is_over = false;
    }
    /// @brief 配列に新しく要素xを追加。最も古い要素は上書きされる場合あり
    /// @param x 追加する要素
    inline void Add(T x) {
        data_[idx_] = x;
        idx_++;
        if(idx_ >= SZ) {
            idx_ %= SZ;
            is_over = true;
        }
    }
    /// @brief 条件を満たす要素が配列内に存在するか判定 存在量化
    /// @param condition 条件式=要素を受け取ってbool返す関数
    /// @return 1つでも存在すればT, 1つも無ければF
    bool ExistSuchThat(std::function<bool(T)> condition) const {
        for(int i = 0; i < SZ; i++) {
            if(condition(data_[i])) {
                return true;
            }
        }
        return false;
    }
    /// @brief 全ての要素が条件を満たすか判定 全称量化
    /// @param condition 条件式=要素を受け取ってbool返す関数
    /// @return 全て満たした時だけT, そうでないならF
    bool AllMeet(std::function<bool(T)> condition) const {
        for(int i = 0; i < SZ; i++) {
            if(!condition(data_[i])) {
                return false;
            }
        }
        return true;
    }
    /// @brief 配列の全要素を関数fの出力に置換; A_i = f(A_i, i)
    /// @param f f:要素->要素なる関数
    void Mapping(std::function<T(T)> f) {
        for(int i = 0; i < SZ; i++) {
            data_[i] = f(data_[i]);
        }
    }
    /// @brief indexも考慮し配列の全要素を関数fの出力に置換; A_i = f(A_i, i)
    /// @param f 関数 index情報としてintも取る
    void Mapping(std::function<T(T, int)> f) {
        for(int i = 0; i < SZ; i++) {
            data_[i] = f(data_[i], i);
        }
    }

    void operator+=(CirculatedArr<T, SZ> const &le) {
        for(int i = 0; i < SZ; i++) {
            this->data_[i] += le.data_[i];
        }
    }
    void operator-=(CirculatedArr<T, SZ> const &le) {
        for(int i = 0; i < SZ; i++) {
            this->data_[i] -= le.data_[i];
        }
    }
    void operator|=(std::function<T(T, int)> f) {
        for(int i = 0; i < SZ; i++) {
            data_[i] = f(data_[i], i);
        }
    }

    void dump() {
        using namespace std;
        for(size_t i = 0; i < 10; i++) {
            cout << this->data_[i] << " ";
        }
        cout << endl;
    }
};