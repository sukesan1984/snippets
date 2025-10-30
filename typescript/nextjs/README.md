# Next.js + TypeScript + Docker Skeleton

Frontend と Backend を分離した Next.js + TypeScript のスケルトンアプリケーションです。

## 構成

### 基本構成
- **Frontend**: Next.js 14 + TypeScript (ポート3002)
- **Docker**: Frontend/Backend別々のコンテナで構成

### バックエンドの選択肢
1. **Next.js API Routes (同一プロセス)**: フロントエンドと一体型 (ポート3002)
2. **Next.js Backend (専用インスタンス)**: API専用のNext.jsアプリ (ポート3004)
3. **同一コード別プロセス**: frontendアプリを別プロセスで起動 (ポート3005)
4. **Express版**: REST API (ポート3001)
5. **tRPC + Hono版**: 型安全なRPC (ポート3003)

## セットアップ

### 開発環境の起動

#### Express バックエンド版
```bash
# 開発用Docker環境の起動
docker-compose -f docker-compose.dev.yml up --build

# バックグラウンドで起動する場合
docker-compose -f docker-compose.dev.yml up -d --build
```

#### Next.js Backend 版（専用インスタンス）
```bash
# Next.js Backend版の開発環境起動
docker-compose -f docker-compose-nextjs.yml up --build

# バックグラウンドで起動する場合
docker-compose -f docker-compose-nextjs.yml up -d --build
```

#### 同一コード別プロセス版
```bash
# frontendアプリを別プロセスでバックエンドとして起動
docker-compose -f docker-compose-frontend-as-backend.yml up --build

# バックグラウンドで起動する場合
docker-compose -f docker-compose-frontend-as-backend.yml up -d --build
```

#### tRPC + Hono バックエンド版
```bash
# tRPC版の開発環境起動
docker-compose -f docker-compose-trpc.yml up --build

# バックグラウンドで起動する場合
docker-compose -f docker-compose-trpc.yml up -d --build
```

### 本番環境の起動

```bash
# 本番用Docker環境の起動
docker-compose up --build
```

### ローカル開発（Docker未使用）

```bash
# Backend
cd backend
npm install
npm run dev

# Frontend（別ターミナル）
cd frontend
npm install
npm run dev
```

## アクセスURL

- Frontend: http://localhost:3002
- Backend API (Express): http://localhost:3001
- Backend API (tRPC + Hono): http://localhost:3003
- Backend API (Next.js Separate): http://localhost:3004
- 比較ページ: http://localhost:3002/compare-standalone

## APIエンドポイント

### Next.js API Routes (ポート3002)
- `GET /api/nextjs/health` - ヘルスチェック
- `GET /api/nextjs/hello` - サンプルメッセージ取得
- `POST /api/nextjs/echo` - メッセージをエコー

### Express REST API (ポート3001)
- `GET /api/health` - ヘルスチェック
- `GET /api/hello` - サンプルメッセージ取得
- `POST /api/echo` - メッセージをエコー

### tRPC + Hono (ポート3003)
- `/trpc/health` - ヘルスチェック
- `/trpc/hello` - サンプルメッセージ取得
- `/trpc/echo` - メッセージをエコー

## スクリプト

### Backend
- `npm run dev` - 開発サーバー起動（ホットリロード付き）
- `npm run build` - TypeScriptのビルド
- `npm run start` - 本番サーバー起動
- `npm run lint` - ESLint実行
- `npm run type-check` - 型チェック

### Frontend
- `npm run dev` - 開発サーバー起動
- `npm run build` - 本番ビルド
- `npm run start` - 本番サーバー起動
- `npm run lint` - ESLint実行
- `npm run type-check` - 型チェック

## ディレクトリ構成

```
.
├── backend/
│   ├── src/
│   │   └── index.ts        # APIサーバーのエントリーポイント
│   ├── Dockerfile
│   ├── package.json
│   └── tsconfig.json
├── frontend/
│   ├── app/
│   │   ├── layout.tsx      # レイアウトコンポーネント
│   │   ├── page.tsx        # ホームページ
│   │   └── globals.css     # グローバルスタイル
│   ├── public/
│   ├── Dockerfile
│   ├── next.config.js
│   ├── package.json
│   └── tsconfig.json
├── docker-compose.yml       # 本番用Docker構成
├── docker-compose.dev.yml   # 開発用Docker構成
└── README.md
```