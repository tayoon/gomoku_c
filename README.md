# gomoku_c
講義「プログラミングC言語Ⅲ」囲碁ゲーム作成

# Feature
黒手（先手）
- 1手目 - (8,8)
- 2手目
  - 白手：斜め - 直線にならないように初手に対し斜め
  - 白手：縦横 - 初手に対し斜め

白手（後手）
- 1手目 - 先手の周り8マスにランダム配置

碁石カウント - 評価値に重きを置く
- 評価値優先順位
- 五連 > 禁じ手 > 四三 > 四連 > 四三(*) > 三連 > 四連(*) > 二連 > 三連(*)
- (*):碁列の端が碁盤の端
