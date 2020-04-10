
Digispark ATtiny85をUSBマウスとして使い、一定時間ごとにわずかにマウスを動かすことでPCのスリープを抑制します。

# 配線など

LEDが0番につながっているものと1番につながっているものがあるので、必要に応じて読み替えてください
配線は何もいじらず、このまま使っても利用できますが、停止ボタンをつけたい場合はPIN_BUTTONで設定したピンにボタンを接続してください。
（指定ポートをPullupした上で、ボタンを介してGNDに接続)

MOUSE_MOVE_RANDOMを定義すると、マウスを大げさにわかりやすく動かします。
 
# Author
 
Ryusuke Hotta
 
# License

[MIT license](https://en.wikipedia.org/wiki/MIT_License).
