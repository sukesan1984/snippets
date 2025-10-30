import { createTRPCProxyClient, httpBatchLink } from '@trpc/client';
import type { AppRouter as HonoAppRouter } from '../../backend-trpc-hono/src/routers/appRouter';
import type { AppRouter as FastifyAppRouter } from '../../backend-trpc-fastify/src/routers/appRouter';
import type { NextjsTRPCRouter } from './server-trpc';
import superjson from 'superjson';

// tRPC + Hono client
export const trpcHono = createTRPCProxyClient<HonoAppRouter>({
  transformer: superjson,
  links: [
    httpBatchLink({
      url: 'http://localhost:3003/trpc',
    }),
  ],
});

// tRPC + Fastify client  
export const trpcFastify = createTRPCProxyClient<FastifyAppRouter>({
  transformer: superjson,
  links: [
    httpBatchLink({
      url: 'http://localhost:3006/trpc',
    }),
  ],
});

// Next.js内蔵 tRPC client
export const trpcNextjs = createTRPCProxyClient<NextjsTRPCRouter>({
  transformer: superjson,
  links: [
    httpBatchLink({
      url: '/api/trpc',
    }),
  ],
});

// 同一コード別プロセス tRPC client
export const trpcSameCode = createTRPCProxyClient<NextjsTRPCRouter>({
  transformer: superjson,
  links: [
    httpBatchLink({
      url: 'http://localhost:3005/api/trpc',
    }),
  ],
});