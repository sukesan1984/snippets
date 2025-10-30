import { NextResponse } from 'next/server';

export async function GET() {
  return NextResponse.json({
    message: 'Hello from Next.js Backend (Separate Process)',
    timestamp: new Date().toISOString(),
    port: 3004,
  });
}