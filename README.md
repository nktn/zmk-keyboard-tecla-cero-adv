
# CERO/ADV

TECLA-CERO/Adv 分割キーボード用のZMKファームウェア

## 特徴

- キーマトリクスは5行 × 4列 × 2側
- 実入力数は片側23、左右合計46
- 左右両側にトラックボール（PAW3222）搭載
- ROW4に5方向タクトスイッチを接続
- BMP Boost使用
- BLE/USB両対応
- ZMK Studio対応（キーマップをリアルタイム編集可能）
- 右側をセントラル、左側をペリフェラルとして使用

## ビルド
このブランチでは
GitHub Actionsで自動ビルドされます。pushするとビルドが実行され、Artifactsからuf2ファイルをダウンロードできます。

[dya_studioブランチ](https://github.com/nktn/zmk-keyboard-tecla-cero-adv/tree/dya_studio)に変えるとdya studio対応で運用できます

### ビルドアーティファクト

| ファイル名 | 説明 |
|-----------|------|
| `tecla_cero_right_central_with_trackpad` | 右側（セントラル）- トラックパッドあり |
| `tecla_cero_right_central_no_trackpad` | 右側（セントラル）- トラックパッドなし |
| `tecla_cero_left_peripheral_with_trackpad` | 左側（ペリフェラル）- トラックパッドあり |
| `tecla_cero_left_peripheral_no_trackpad` | 左側（ペリフェラル）- トラックパッドなし |
| `settings_reset` | 設定リセット用 |

`with_trackpad` はミニトラックパッドも有効にする構成です。左右のトラックボールはどちらの構成でも有効です。

## 書き込み

1. `tecla_cero_right_central_*` のuf2を右側に書き込み
2. `tecla_cero_left_peripheral_*` のuf2を左側に書き込み

左右で `with_trackpad` / `no_trackpad` を揃えてください。

## 入力デバイス

- 右トラックボール: 右側セントラルでローカル入力
- 左トラックボール: split inputとして右側セントラルへ転送
- ミニトラックパッド: `with_trackpad` 構成のみ有効、スクロール入力として使用。利用する場合はbmp_boost_extender_miniの基板を経由してミニトラックパッドを利用してください。

## ５方向タクトスイッチ

動作確認用に以下を割り当てています。

| 左側5方向 | 右側5方向 |
|-----------|-----------|
| ← / ↓ / ↑ / → / Enter | Middle Click / Left Click / Right Click / Scroll Up / Scroll Down |

## キーマップ編集

- [ZMK Studio](https://zmk.studio/)でリアルタイム編集可能
- `config/keymap.keymap`を直接編集してpushすることも可能
