このディレクトリではSBFWを応用しつつ、STG用の画面を制作する。

戦闘画面、リザルト画面はSimpeSceneを継承したクラスを用意する。(GameScene, ResultScene)
それ以外はSBFWの既存メソッド`AddImage(),AddButton()`で表現する。(main.cppで定義されている)


PngTextureとLocationは大幅整理前(SBFWの分離以前)のクラスであまり使いたくないが、internalとの雑多な座標系変換関数がこのクラスを元に作られてしまっている。これを用意し直すのは極めて大変なので流用する。
PngTextureはbindidを何度も切り替えているのでとても遅いので今後の利用は非推奨。新規で使用してはいけない。


```c++
class Combine {
    public:
    int score, bestscore,.....;
    Combine();
    /// 再代入用
    Combine(int x, int y, ....);
};

Combine combine = Combine(); /// 定義

class GameScene{
    void func(){
        /// if ゲーム終了
        combine = Combine(Battle.GetBestScore(), Battle.GetScore(), .....);
        GoNextScene(ResultScene)
    }
}
class ResultScene{
    void func(){
        number_display.Draw(combine.GetBestScore())
    }
}

```