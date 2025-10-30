import { NextRequest, NextResponse } from 'next/server';

export async function POST(request: NextRequest) {
  try {
    const body = await request.json();
    const { message } = body;

    return NextResponse.json({
      echo: message,
      timestamp: new Date().toISOString(),
      source: 'Next.js Backend (Separate Process)',
      port: 3004,
    });
  } catch (error) {
    return NextResponse.json(
      { error: 'Invalid request body' },
      { status: 400 }
    );
  }
}