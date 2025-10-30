import { z } from 'zod';
import { router, publicProcedure } from '../trpc';
import { prisma } from '@shared/prisma';

export const appRouter = router({
  health: publicProcedure.query(() => {
    return {
      status: 'ok',
      timestamp: new Date().toISOString(),
    };
  }),

  hello: publicProcedure.query(() => {
    return {
      message: 'Hello from tRPC + Hono Backend',
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
    .mutation(async ({ input }) => {
      const user = await prisma.user.create({
        data: {
          name: input.name,
          email: input.email,
        },
      });
      return user;
    }),

  // Prismaを使ったユーザー取得
  getUsersFromDB: publicProcedure.query(async () => {
    const users = await prisma.user.findMany({
      include: {
        posts: true,
      },
    });
    return users;
  }),
});

export type AppRouter = typeof appRouter;