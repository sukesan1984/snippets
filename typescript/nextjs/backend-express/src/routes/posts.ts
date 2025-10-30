import { Router, Request, Response } from 'express';
import { prisma } from '../../shared/prisma/src/index';

const router = Router();

// 全ポスト取得
router.get('/', async (_req: Request, res: Response) => {
  try {
    const posts = await prisma.post.findMany({
      include: {
        author: true,
      },
    });
    res.json(posts);
  } catch (error) {
    res.status(500).json({ error: 'Failed to fetch posts' });
  }
});

// ポスト取得（ID）
router.get('/:id', async (req: Request, res: Response) => {
  try {
    const { id } = req.params;
    const post = await prisma.post.findUnique({
      where: { id: parseInt(id) },
      include: {
        author: true,
      },
    });
    
    if (!post) {
      return res.status(404).json({ error: 'Post not found' });
    }
    
    res.json(post);
  } catch (error) {
    res.status(500).json({ error: 'Failed to fetch post' });
  }
});

// ポスト作成
router.post('/', async (req: Request, res: Response) => {
  try {
    const { title, content, published, authorId } = req.body;
    
    if (!title) {
      return res.status(400).json({ error: 'Title is required' });
    }
    
    const post = await prisma.post.create({
      data: {
        title,
        content,
        published: published || false,
        authorId: authorId ? parseInt(authorId) : undefined,
      },
      include: {
        author: true,
      },
    });
    
    res.status(201).json(post);
  } catch (error) {
    res.status(500).json({ error: 'Failed to create post' });
  }
});

// ポスト更新
router.put('/:id', async (req: Request, res: Response) => {
  try {
    const { id } = req.params;
    const { title, content, published, authorId } = req.body;
    
    const post = await prisma.post.update({
      where: { id: parseInt(id) },
      data: {
        title,
        content,
        published,
        authorId: authorId ? parseInt(authorId) : undefined,
      },
      include: {
        author: true,
      },
    });
    
    res.json(post);
  } catch (error: any) {
    if (error.code === 'P2025') {
      res.status(404).json({ error: 'Post not found' });
    } else {
      res.status(500).json({ error: 'Failed to update post' });
    }
  }
});

// ポスト削除
router.delete('/:id', async (req: Request, res: Response) => {
  try {
    const { id } = req.params;
    
    await prisma.post.delete({
      where: { id: parseInt(id) },
    });
    
    res.status(204).send();
  } catch (error: any) {
    if (error.code === 'P2025') {
      res.status(404).json({ error: 'Post not found' });
    } else {
      res.status(500).json({ error: 'Failed to delete post' });
    }
  }
});

export default router;