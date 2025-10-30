#!/bin/bash
# Prisma マイグレーション実行スクリプト

set -e

echo "🔄 Running Prisma migrations..."

# マイグレーション実行
npx prisma migrate dev --name "${1:-auto-migration}"

echo "✅ Migrations completed!"

# Prisma クライアント生成
echo "🔧 Generating Prisma client..."
npx prisma generate

echo "✅ Prisma client generated!"
echo "🎉 Database is ready!"