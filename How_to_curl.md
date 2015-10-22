# curl教學

如果要貼code到工作站，又怕code格式跑掉，可以使用`curl`這個功能! 這個功能方便又有效!

感謝丕佑提供技術支援!

# 基本操作

1. 進入[Gists](https://gist.github.com/ "Gists from github")，並將code貼上，並按下create public gist

2. 點螢幕中間的`raw`，會顯示_純文字_版本的code

3. 複製網址，應該會類似這樣

`
https://gist.githubusercontent.com/anonymous/fdac431f9feb9ca08ffd/raw/ede9847a104b4f36ac2b4c2e4a6f4572a8118326/test
`

4. 登入工作站。 _注意:_ 要用turnin功能，需要在csie0.cs.ccu.edu.tw登入才能用!

5. 在你要存檔案的地方，輸入`curl` 加上 `你剛剛複製的網址`，並且輸入 ` > ` 加上你想要命名的檔案名稱。

例如:

`
curl https://gist.githubusercontent.com/anonymous/09ea94690ef5583be1c5/raw/d59088b9c9c9b255c53dd8ab69b2bfa43922759a/test > test.txt
`

這樣就會把網址所指向的code存到test.txt中!

6. 輸入`turnin ds.HWA `，加上你要交的檔案名稱。 例如: `turnin ds.HWA main.c readme.txt` ，這樣就會一次繳交main.c 和 readme.txt
