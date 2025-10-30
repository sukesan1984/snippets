'use client';

import { useState } from 'react';

export default function Home() {
  const [apiResponse, setApiResponse] = useState<string>('');
  const [loading, setLoading] = useState(false);

  const fetchFromBackend = async () => {
    setLoading(true);
    try {
      const response = await fetch('/api/hello');
      const data = await response.json();
      setApiResponse(JSON.stringify(data, null, 2));
    } catch (error) {
      setApiResponse(`Error: ${error}`);
    } finally {
      setLoading(false);
    }
  };

  const testEcho = async () => {
    setLoading(true);
    try {
      const response = await fetch('/api/echo', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({ message: 'Hello from Frontend!' }),
      });
      const data = await response.json();
      setApiResponse(JSON.stringify(data, null, 2));
    } catch (error) {
      setApiResponse(`Error: ${error}`);
    } finally {
      setLoading(false);
    }
  };

  return (
    <div className="container">
      <h1 className="title">Next.js + TypeScript + Docker</h1>
      <p className="description">
        Frontend と Backend が分離された構成のスケルトンアプリケーション
      </p>
      
      <div style={{ marginBottom: '2rem', marginTop: '2rem' }}>
        <a href="/compare-standalone" style={{ color: '#0070f3', textDecoration: 'underline' }}>
          → REST API vs tRPC 比較ページへ
        </a>
      </div>
      
      <div>
        <button className="button" onClick={fetchFromBackend} disabled={loading}>
          {loading ? 'Loading...' : 'Fetch from Backend API'}
        </button>
        {' '}
        <button className="button" onClick={testEcho} disabled={loading}>
          {loading ? 'Loading...' : 'Test Echo API'}
        </button>
      </div>

      {apiResponse && (
        <pre className="apiResponse">
          {apiResponse}
        </pre>
      )}
    </div>
  );
}