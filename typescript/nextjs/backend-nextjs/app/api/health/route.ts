import { NextResponse } from 'next/server';

export async function GET() {
  return NextResponse.json({
    status: 'ok',
    timestamp: new Date().toISOString(),
    service: 'Next.js Backend (Separate Process)',
    version: '14.2.16',
    port: 3004,
    pid: process.pid,
  });
}