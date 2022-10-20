# プロジェクト-シューティング

- [予定](#予定)
```mermaid
gantt
dateFormat  YYYY-MM-DD
axisFormat  %m/%d
title シューティングゲーム制作フロー

section 松尾
企画検討 : active, task1, 2022-10-15,2022-10-20
仕様書作成      :  task2, after task1, 6d
プロトタイプ作成: task3, after task2, 7d
デザイン修正: task4, after task3, 7d
完成版作成: task5, after task4, 7d

section 岩渕
企画検討 : active, task1, 2022-10-15,2022-10-20
C++GUI選定 : active, task_select, 2022-10-15,2022-10-20
仕様書作成      :  task2, after task1, 6d
プロトタイプ作成: task3, after task2, 7d 
デザイン修正: task4, after task3, 7d
完成版作成: task5, after task4, 7d
```
## ゲーム制作フロー
1. 企画・検討
・パワーポイント5枚程度でゲームの説明

2. 仕様書作成
・機能仕様
・非機能仕様
・デザイン
・クラス図
・世界観仕様

3. プロトタイプ作成
・最低限仕様を満たすゲームのプログラム

4. デザイン修正
・プロトタイプの内容を元に足りない部分を列挙

5. 完成版作成
・遊べるゲームを目指してプログラム

6. デバッグ
・バグチェック等、デバッグを通じて修正

7. 完成(終了)
・必要に応じてルールブックの作成

## 検討GUI
* Qt: Javaで言うSwingみたいなGUIライブラリ、フレームワーク。C++だけで作ることができる。
* JS + WASM: WebAssemblyによりC++コードをWeb上で実行できるようになる。描画はJavaScriptが担当する。
* openGLが良いと思う
多分非Unix環境ではQtとWASMはインストールが難しそう。WSLがWindowsに入りそうなら良いんだけど

https://onlinegdb.com/kGYo98t65


https://note.com/ukyousan/n/neea2e631702b#uD9c6
サンプル3を参考に 各画面の説明

サンプル1が画面遷移図
データフローダイアグラム

```mermaid
classDiagram
  class title {
    +str name
    #int Age
  }

  class Id { -int value }
  class Age { -int value }
  class Owner
  class Employee {
    +int Id

    +int get_age()
  }
title--> 戦闘
class 戦闘{
    null
}


  Human <|-- Owner : extends
  Human <|-- Employee : extends
  Human o-- Id
  Human o-- Age
  Owner --> Employee : use
```
## 画面遷移図
```mermaid
graph LR;
    タイトル-->デッキ編成
    デッキ編成-->タイトル
    デッキ編成-->所持カード
    所持カード-->デッキ編成
    タイトル-->戦闘
    戦闘-->終了画面
    終了画面-->タイトル
```
所持カードはウィンドウ