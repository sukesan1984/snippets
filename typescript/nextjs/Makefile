.PHONY: help up down status logs clean install build

# デフォルトターゲット
help:
	@echo "利用可能なコマンド:"
	@echo "  make up                 - すべてのバックエンドを起動"
	@echo "  make down               - すべてのバックエンドを停止"
	@echo "  make status             - 起動中のコンテナを表示"
	@echo "  make logs               - すべてのログを表示"
	@echo "  make clean              - すべてを停止して削除"
	@echo "  make install            - 依存関係をインストール"
	@echo "  make build              - Dockerイメージをビルド"

# すべてのバックエンドを起動
up:
	@echo "🚀 すべてのバックエンドを起動中..."
	docker-compose up -d --build
	@echo ""
	@echo "✅ すべてのサービスが起動しました！"
	@echo ""
	@echo "📌 アクセスURL:"
	@echo "  - Frontend: http://localhost:3002"
	@echo "  - Express Backend: http://localhost:3001"
	@echo "  - tRPC + Hono Backend: http://localhost:3003"
	@echo "  - tRPC + Fastify Backend: http://localhost:3006"
	@echo "  - Next.js Backend: http://localhost:3004"
	@echo "  - Frontend as Backend: http://localhost:3005"
	@echo "  - 比較ページ: http://localhost:3002/compare-standalone"
	@echo ""
	@make status

# すべてのバックエンドを停止
down:
	@echo "🛑 すべてのバックエンドを停止中..."
	docker-compose down
	@echo "✅ すべてのサービスが停止しました"


# 状態確認
status:
	@echo "📊 起動中のコンテナ:"
	@docker ps --filter "name=backend" --filter "name=frontend" --format "table {{.Names}}\t{{.Ports}}\t{{.Status}}"

# ログ表示（すべて）
logs:
	docker-compose logs -f


# クリーンアップ
clean:
	@echo "🧹 すべてを停止して削除中..."
	docker-compose down -v --remove-orphans
	@echo "✅ クリーンアップ完了"

# 依存関係のインストール
install:
	@echo "📦 依存関係をインストール中..."
	cd frontend && npm install
	cd backend-express && npm install
	cd backend-trpc-hono && npm install
	cd backend-trpc-fastify && npm install
	cd backend-nextjs && npm install
	@echo "✅ インストール完了"

# ビルドのみ
build:
	@echo "🔨 すべてのイメージをビルド中..."
	docker-compose build
	@echo "✅ ビルド完了"