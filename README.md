# gomoku_c
講義「プログラミングC言語Ⅲ」囲碁ゲーム作成

# Feature
### Black (first move)
- 1st - (8,8)
- 2nd
  - white: diagonal - diagonal to the 1st black move to avoid a straight line
  - white: vertical and horizontal - diagonal to the 1st black move

### White (second move)
- 1st - randomly placed in 8 squares around the 1st black move

### Go stone count - focus on evaluation value
- Priority of evaluation value
- 五連 > 禁じ手 > 四三 > 四連 > 四三(") > 三連 > 四連(") > 二連 > 三連(")
- ("):The end of the line is the end of the board
