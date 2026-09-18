# NTHU_BlueCapeFlyingCat_CodeBook

## 下載 Codebook
```sh
git clone https://github.com/temmie-950807/NTHU_BlueCapeFlyingCat_CodeBook.git
```

## 編譯 Codebook
```sh
cd NTHU_BlueCapeFlyingCat_CodeBook
# 全彩模式 (預設)
python3 build.py

# 黑白模式 (僅使用黑白之間的顏色，適合黑白列印)
python3 build.py --black

# 查看說明
python3 build.py help
```

在某些作業系統中，要將 `python3` 換成 `python`。

## Dependencies
- python (version >= 3.0)
- xelatex (latest version)

### Install xelatex
For Linux
```sh
apt install texlive-xetex
```

If still cannot build:

```sh
apt install texlive-full
```

For Windows
Install MiKTeX https://miktex.org/download

For Mac
```sh
brew install texlive
```