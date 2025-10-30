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
	@echo ""
	@echo "個別起動コマンド:"
	@echo "  make up-express          - Express版のみ起動"
	@echo "  make up-trpc            - tRPC+Hono版のみ起動"
	@echo "  make up-nextjs          - Next.js Backend版のみ起動"
	@echo "  make up-frontend-backend - 同一コード別プロセス版のみ起動"

# すべてのバックエンドを起動（統合docker-compose使用）
up:
	@echo "🚀 すべてのバックエンドを起動中..."
	docker-compose -f docker-compose.all.yml up -d --build
	@echo ""
	@echo "✅ すべてのサービスが起動しました！"
	@echo ""
	@echo "📌 アクセスURL:"
	@echo "  - Frontend: http://localhost:3002"
	@echo "  - Express Backend: http://localhost:3001"
	@echo "  - tRPC + Hono Backend: http://localhost:3003"
	@echo "  - Next.js Backend: http://localhost:3004"
	@echo "  - Frontend as Backend: http://localhost:3005"
	@echo "  - 比較ページ: http://localhost:3002/compare-standalone"
	@echo ""
	@make status

# すべてのバックエンドを停止
down:
	@echo "🛑 すべてのバックエンドを停止中..."
	docker-compose -f docker-compose.all.yml down
	@echo "✅ すべてのサービスが停止しました"

# 個別起動コマンド
up-express:
	@echo "🚀 Express版を起動中..."
	docker-compose -f docker-compose.dev.yml up -d --build
	@echo "✅ Express Backend: http://localhost:3001"
	@echo "✅ Frontend: http://localhost:3002"

up-trpc:
	@echo "🚀 tRPC+Hono版を起動中..."
	docker-compose -f docker-compose-trpc.yml up -d --build
	@echo "✅ tRPC + Hono Backend: http://localhost:3003"
	@echo "✅ Frontend: http://localhost:3002"

up-nextjs:
	@echo "🚀 Next.js Backend版を起動中..."
	docker-compose -f docker-compose-nextjs.yml up -d --build
	@echo "✅ Next.js Backend: http://localhost:3004"
	@echo "✅ Frontend: http://localhost:3002"

up-frontend-backend:
	@echo "🚀 同一コード別プロセス版を起動中..."
	docker-compose -f docker-compose-frontend-as-backend.yml up -d --build
	@echo "✅ Frontend as Backend: http://localhost:3005"
	@echo "✅ Frontend: http://localhost:3002"

# 状態確認
status:
	@echo "📊 起動中のコンテナ:"
	@docker ps --filter "name=backend" --filter "name=frontend" --format "table {{.Names}}\t{{.Ports}}\t{{.Status}}"

# ログ表示（すべて）
logs:
	docker-compose -f docker-compose.all.yml logs -f

# ログ表示（個別）
logs-express:
	docker-compose -f docker-compose.dev.yml logs -f

logs-trpc:
	docker-compose -f docker-compose-trpc.yml logs -f

logs-nextjs:
	docker-compose -f docker-compose-nextjs.yml logs -f

logs-frontend:
	docker-compose -f docker-compose-frontend-as-backend.yml logs -f

# クリーンアップ
clean:
	@echo "🧹 すべてを停止して削除中..."
	docker-compose -f docker-compose.all.yml down -v --remove-orphans
	@echo "✅ クリーンアップ完了"

# 依存関係のインストール
install:
	@echo "📦 依存関係をインストール中..."
	cd frontend && npm install
	cd backend && npm install
	cd backend-trpc && npm install
	cd backend-nextjs && npm install
	@echo "✅ インストール完了"

# ビルドのみ
build:
	@echo "🔨 すべてのイメージをビルド中..."
	docker-compose -f docker-compose.all.yml build
	@echo "✅ ビルド完了"