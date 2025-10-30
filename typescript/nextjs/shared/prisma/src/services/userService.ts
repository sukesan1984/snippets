import { prisma } from '../index';
import type { User, Post, Prisma } from '@prisma/client';

export interface UserWithPosts extends User {
  posts: Post[];
}

export class UserService {
  // 全ユーザー取得
  static async getAllUsers(): Promise<UserWithPosts[]> {
    return prisma.user.findMany({
      include: {
        posts: true,
      },
    });
  }

  // ユーザー取得（ID）
  static async getUserById(id: number): Promise<UserWithPosts | null> {
    return prisma.user.findUnique({
      where: { id },
      include: {
        posts: true,
      },
    });
  }

  // ユーザー作成
  static async createUser(data: Prisma.UserCreateInput): Promise<User> {
    return prisma.user.create({
      data,
    });
  }

  // ユーザー更新
  static async updateUser(id: number, data: Prisma.UserUpdateInput): Promise<User> {
    return prisma.user.update({
      where: { id },
      data,
    });
  }

  // ユーザー削除
  static async deleteUser(id: number): Promise<User> {
    return prisma.user.delete({
      where: { id },
    });
  }
}