import { initTRPC } from '@trpc/server';
import { z } from 'zod';
import superjson from 'superjson';

const t = initTRPC.create({
  transformer: superjson,
});

export const router = t.router;
export const publicProcedure = t.procedure;

// Next.js内蔵のtRPCルーター
export const appRouter = router({
  hello: publicProcedure.query(() => {
    return {
      message: 'Hello from Next.js tRPC (Same Process)',
      timestamp: new Date().toISOString(),
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

  health: publicProcedure.query(() => {
    return {
      status: 'ok',
      timestamp: new Date().toISOString(),
    };
  }),
});

export type NextjsTRPCRouter = typeof appRouter;