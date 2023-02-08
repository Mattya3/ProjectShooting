// GLFWを隠蔽、cppファイルでのみincludeするためにこの前方宣言必要
class GLFWwindow;

// ヘルパ関数を定義する
namespace sbfw {

extern int window_width, window_height;
namespace detail {
extern GLFWwindow *window;
void CheckInited();
} // namespace detail
}