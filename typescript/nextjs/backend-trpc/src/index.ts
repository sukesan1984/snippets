import { Hono } from 'hono';
import { serve } from '@hono/node-server';
import { cors } from 'hono/cors';
import { trpcServer } from '@hono/trpc-server';
import { appRouter } from './routers/appRouter';

const app = new Hono();
const PORT = process.env.PORT || 3003;

app.use('/*', cors());

app.use(
  '/trpc/*',
  trpcServer({
    router: appRouter,
  })
);

app.get('/', (c) => {
  return c.json({ 
    message: 'tRPC + Hono Server',
    trpcEndpoint: '/trpc',
  });
});

console.log(`tRPC + Hono server is running on port ${PORT}`);
console.log(`tRPC Playground: http://localhost:${PORT}/trpc`);

serve({
  fetch: app.fetch,
  port: Number(PORT),
});