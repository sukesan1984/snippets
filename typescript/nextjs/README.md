# Next.js + TypeScript バックエンドパターン比較プロジェクト

このプロジェクトは、Next.js + TypeScriptを使用した6つの異なるバックエンド実装パターンを比較するためのサンプル集です。各パターンの特徴、メリット・デメリットを実際に動作させながら学習できます。

## 🏗️ アーキテクチャ概要

```
┌─ frontend/                    # メインフロントエンド（ポート3002）
├─ backend-express/            # Express REST API（ポート3001）
├─ backend-trpc-hono/          # tRPC + Hono（ポート3003）
├─ backend-trpc-fastify/       # tRPC + Fastify（ポート3006）
├─ backend-nextjs/             # Next.js専用バックエンド（ポート3004）
├─ docker-compose.yml          # 全サービス統合起動設定
└─ Makefile                    # 便利コマンド集
```

## 📋 実装パターン一覧

### 1. Next.js API Routes (同一プロセス)
- **ポート**: 3002
- **特徴**: フロントエンドと同じプロセスで動作
- **メリット**: 開発・デプロイが最も簡単
- **デメリット**: フロントエンドとバックエンドが密結合

### 2. 同一コード別プロセス
- **ポート**: 3005
- **特徴**: 同じfrontendコードを別プロセスで起動
- **メリット**: コードベース統一、スケールが容易
- **デメリット**: 不要なフロントエンドコードも含む

### 3. Next.js Backend (別プロセス)
- **ポート**: 3004
- **特徴**: バックエンド専用のNext.jsインスタンス
- **メリット**: Next.jsの恩恵を受けつつ分離
- **デメリット**: 別途Next.jsプロジェクトの管理が必要

### 4. Express (REST API)
- **ポート**: 3001
- **特徴**: 従来のREST APIサーバー
- **メリット**: 最も広く使われている、豊富なエコシステム
- **デメリット**: 型安全性がない、手動でのAPI定義が必要

### 5. tRPC + Hono
- **ポート**: 3003
- **特徴**: 型安全なRPCフレームワーク + 軽量Webフレームワーク
- **メリット**: 完全な型安全性、高性能
- **デメリット**: 学習コスト、エコシステムがまだ発展途上

### 6. tRPC + Fastify
- **ポート**: 3006
- **特徴**: 型安全なRPCフレームワーク + 高性能Webフレームワーク
- **メリット**: 完全な型安全性、Fastifyの高性能とプラグインシステム
- **デメリット**: 学習コスト、設定が複雑

## 🚀 クイックスタート

### 前提条件
- Node.js 20以上
- Docker & Docker Compose
- npm

### すべてのサービスを起動

```bash
# 依存関係をインストール
make install

# 全サービスを起動
make up
```

### 個別でのインストールと起動

```bash
# 各ディレクトリで依存関係をインストール
cd frontend && npm install
cd ../backend-express && npm install
cd ../backend-trpc-hono && npm install
cd ../backend-trpc-fastify && npm install
cd ../backend-nextjs && npm install

# Docker Composeで起動
docker-compose up -d --build
```

## 📊 比較ページ

すべてのサービスが起動したら、以下のURLで各パターンを試すことができます：

- **比較ページ**: http://localhost:3002/compare-standalone
- **メインフロントエンド**: http://localhost:3002

比較ページでは、6つのパターンすべてに対して同じAPIリクエストを送信し、レスポンスを比較できます。

## 🛠️ 利用可能なコマンド

```bash
# 全サービス起動
make up

# 全サービス停止
make down

# サービス状態確認
make status

# ログ確認
make logs

# 完全クリーンアップ
make clean

# 依存関係インストール
make install

# Dockerイメージビルドのみ
make build

# ヘルプ表示
make help
```

## 🌐 各サービスのエンドポイント

### Express Backend (3001)
```bash
curl http://localhost:3001/api/hello
curl -X POST http://localhost:3001/api/echo -H "Content-Type: application/json" -d '{"message":"test"}'
```

### tRPC + Hono (3003)
```bash
curl http://localhost:3003/trpc/hello
curl -X POST http://localhost:3003/trpc/echo -H "Content-Type: application/json" -d '{"json":{"message":"test"}}'
```

### tRPC + Fastify (3006)
```bash
curl http://localhost:3006/trpc/hello
curl -X POST http://localhost:3006/trpc/echo -H "Content-Type: application/json" -d '{"json":{"message":"test"}}'
```

### Next.js Backend (3004)
```bash
curl http://localhost:3004/api/hello
curl -X POST http://localhost:3004/api/echo -H "Content-Type: application/json" -d '{"message":"test"}'
```

### Frontend as Backend (3005)
```bash
curl http://localhost:3005/api/nextjs/hello
curl -X POST http://localhost:3005/api/nextjs/echo -H "Content-Type: application/json" -d '{"message":"test"}'
```

### Next.js API Routes (3002)
```bash
curl http://localhost:3002/api/nextjs/hello
curl -X POST http://localhost:3002/api/nextjs/echo -H "Content-Type: application/json" -d '{"message":"test"}'
```

## 📁 ディレクトリ構成詳細

```
.
├── README.md
├── Makefile
├── docker-compose.yml
├── frontend/                   # Next.js フロントエンド
│   ├── app/
│   │   ├── compare-standalone/ # 比較ページ
│   │   └── api/nextjs/        # Next.js API Routes
│   ├── Dockerfile
│   ├── next.config.js
│   ├── package.json
│   └── tsconfig.json
├── backend-express/            # Express REST API
│   ├── src/
│   │   └── index.ts
│   ├── Dockerfile
│   ├── package.json
│   └── tsconfig.json
├── backend-trpc-hono/         # tRPC + Hono
│   ├── src/
│   │   ├── index.ts
│   │   ├── trpc.ts
│   │   └── routers/
│   │       └── appRouter.ts
│   ├── Dockerfile
│   ├── package.json
│   └── tsconfig.json
├── backend-trpc-fastify/      # tRPC + Fastify
│   ├── src/
│   │   ├── index.ts
│   │   ├── trpc.ts
│   │   └── routers/
│   │       └── appRouter.ts
│   ├── Dockerfile
│   ├── package.json
│   └── tsconfig.json
└── backend-nextjs/            # Next.js Backend
    ├── app/
    │   └── api/
    ├── Dockerfile
    ├── next.config.js
    ├── package.json
    └── tsconfig.json
```

## 🔧 技術スタック

- **フロントエンド**: Next.js 14, React, TypeScript
- **バックエンド**: 
  - Express.js + CORS
  - tRPC + Hono
  - tRPC + Fastify
  - Next.js API Routes
- **開発・運用**: Docker, Docker Compose, TypeScript
- **バリデーション**: Zod (tRPCパターン)

## 🎯 学習ポイント

1. **単一プロセス vs 分離**: 開発の簡単さとスケーラビリティのトレードオフ
2. **REST vs RPC**: APIデザインの違いと型安全性の重要性
3. **フレームワーク選択**: パフォーマンス、エコシステム、学習コストの比較
4. **Docker化**: マイクロサービス的な構成での開発・デプロイ
5. **CORS設定**: フロントエンドとバックエンド分離時の必須設定

## 🚨 注意事項

- このプロジェクトは学習・比較目的です
- 本番環境では適切なセキュリティ設定が必要です
- 各パターンの選択は、プロジェクトの要件に応じて決定してください

## 📚 参考リソース

- [Next.js Documentation](https://nextjs.org/docs)
- [tRPC Documentation](https://trpc.io/)
- [Express.js Documentation](https://expressjs.com/)
- [Hono Documentation](https://hono.dev/)
- [Fastify Documentation](https://www.fastify.io/)