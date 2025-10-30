import { z } from 'zod';
import { router, publicProcedure } from '../trpc';

export const appRouter = router({
  health: publicProcedure.query(() => {
    return {
      status: 'ok',
      timestamp: new Date().toISOString(),
    };
  }),

  hello: publicProcedure.query(() => {
    return {
      message: 'Hello from tRPC + Fastify Backend',
    };
  }),

  echo: publicProcedure
    .input(z.object({
      message: z.string(),
    }))
    .mutation(({ input }) => {
      return {
        echo: input.message,
        timestamp: new Date().toISOString(),
      };
    }),

  getUser: publicProcedure
    .input(z.object({
      id: z.string(),
    }))
    .query(({ input }) => {
      return {
        id: input.id,
        name: `User ${input.id}`,
        email: `user${input.id}@example.com`,
      };
    }),

  createUser: publicProcedure
    .input(z.object({
      name: z.string().min(1),
      email: z.string().email(),
    }))
    .mutation(({ input }) => {
      const id = Math.random().toString(36).substring(7);
      return {
        id,
        name: input.name,
        email: input.email,
        createdAt: new Date().toISOString(),
      };
    }),
});

export type AppRouter = typeof appRouter;