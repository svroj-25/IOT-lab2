#!/usr/bin/env bash
# scripts/switch.sh - Mashqlar o'rtasida oson o'tish skripti

set -e

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
PIO_BIN="$HOME/.platformio/penv/bin/pio"

EX="$1"

if [[ -z "$EX" ]]; then
    echo "Foydalanish: ./scripts/switch.sh <1|2|3|4>"
    echo "Misol: ./scripts/switch.sh 1  (LED chase)"
    echo "       ./scripts/switch.sh 2  (Sensor statistics)"
    echo "       ./scripts/switch.sh 3  (Sensor alert)"
    echo "       ./scripts/switch.sh 4  (Button counter)"
    exit 1
fi

# Agar faqat raqam kiritilgan bo'lsa (masalan 1 -> ex1)
if [[ "$EX" =~ ^[1-4]$ ]]; then
    ENV_NAME="ex$EX"
elif [[ "$EX" =~ ^ex[1-4]$ ]]; then
    ENV_NAME="$EX"
else
    echo "Xato: Faqat 1, 2, 3 yoki 4 kiritilishi kerak!"
    exit 1
fi

echo "=========================================="
echo "🔄 Mashq almashtirilmoqda: $ENV_NAME"
echo "=========================================="

# platformio.ini dagi default_envs ni o'zgartirish
sed -i -E "s/default_envs = ex[1-4]/default_envs = $ENV_NAME/" "$DIR/platformio.ini"

# Build qilish va Wokwi ga nusxalash
echo "🔨 Kompilyatsiya va Wokwiga nusxalash..."
"$PIO_BIN" run -d "$DIR" -e "$ENV_NAME"

echo ""
echo "✅ Muvaffaqiyatli yakunlandi!"
echo "👉 Endi VS Code da Wokwi simulyatorida (diagram.json) 'Play' (Start Simulation) tugmasini bosing."
echo "=========================================="
