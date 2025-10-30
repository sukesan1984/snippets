import Fastify from 'fastify';
import { fastifyTRPCPlugin } from '@trpc/server/adapters/fastify';
import { appRouter } from './routers/appRouter';

const PORT = process.env.PORT || 3006;

async function main() {
  const server = Fastify({
    maxParamLength: 5000,
  });

  // CORS設定
  await server.register(import('@fastify/cors'), {
    origin: true,
    credentials: true,
  });

  // tRPCプラグインを登録
  await server.register(fastifyTRPCPlugin, {
    prefix: '/trpc',
    trpcOptions: { router: appRouter },
  });

  // ルートエンドポイント
  server.get('/', async (request, reply) => {
    return {
      message: 'tRPC + Fastify Server',
      trpcEndpoint: '/trpc',
    };
  });

  try {
    await server.listen({ port: Number(PORT), host: '0.0.0.0' });
    console.log(`tRPC + Fastify server is running on port ${PORT}`);
    console.log(`tRPC Playground: http://localhost:${PORT}/trpc`);
  } catch (err) {
    server.log.error(err);
    process.exit(1);
  }
}

main();