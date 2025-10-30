'use client';

import { useState } from 'react';

export default function CompareStandalonePage() {
  const [restApiResponse, setRestApiResponse] = useState<string>('');
  const [trpcResponse, setTrpcResponse] = useState<string>('');
  const [loading, setLoading] = useState(false);

  // REST API calls to Express backend
  const fetchFromRestAPI = async () => {
    setLoading(true);
    try {
      const response = await fetch('/api/hello');
      const data = await response.json();
      setRestApiResponse(JSON.stringify(data, null, 2));
    } catch (error) {
      setRestApiResponse(`Error: ${error}`);
    } finally {
      setLoading(false);
    }
  };

  const testRestEcho = async () => {
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
      setRestApiResponse(JSON.stringify(data, null, 2));
    } catch (error) {
      setRestApiResponse(`Error: ${error}`);
    } finally {
      setLoading(false);
    }
  };

  // Direct tRPC calls to tRPC backend
  const fetchFromTRPC = async () => {
    setLoading(true);
    try {
      const response = await fetch('http://localhost:3003/trpc/hello', {
        method: 'GET',
        headers: {
          'Content-Type': 'application/json',
        },
      });
      const data = await response.json();
      setTrpcResponse(JSON.stringify(data.result.data, null, 2));
    } catch (error) {
      setTrpcResponse(`Error: ${error}`);
    } finally {
      setLoading(false);
    }
  };

  const testTRPCEcho = async () => {
    setLoading(true);
    try {
      const response = await fetch('http://localhost:3003/trpc/echo', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({
          json: {
            message: 'Hello from Frontend via tRPC!',
          },
        }),
      });
      const data = await response.json();
      setTrpcResponse(JSON.stringify(data.result.data, null, 2));
    } catch (error) {
      setTrpcResponse(`Error: ${error}`);
    } finally {
      setLoading(false);
    }
  };

  return (
    <div className="container">
      <h1 className="title">REST API vs tRPC 比較（スタンドアロン）</h1>
      <p className="description">
        Express REST API と tRPC + Hono の動作比較（直接HTTP呼び出し版）
      </p>
      
      <div style={{ display: 'flex', gap: '2rem', marginTop: '2rem' }}>
        <div style={{ flex: 1 }}>
          <h2>REST API (Express)</h2>
          <p style={{ color: '#666', fontSize: '0.9rem' }}>Port: 3001</p>
          <div style={{ marginTop: '1rem' }}>
            <button className="button" onClick={fetchFromRestAPI} disabled={loading}>
              Fetch Hello
            </button>
            {' '}
            <button className="button" onClick={testRestEcho} disabled={loading}>
              Test Echo
            </button>
          </div>
          {restApiResponse && (
            <pre className="apiResponse">
              {restApiResponse}
            </pre>
          )}
        </div>

        <div style={{ flex: 1 }}>
          <h2>tRPC (Hono)</h2>
          <p style={{ color: '#666', fontSize: '0.9rem' }}>Port: 3003</p>
          <div style={{ marginTop: '1rem' }}>
            <button className="button" onClick={fetchFromTRPC} disabled={loading}>
              Fetch Hello
            </button>
            {' '}
            <button className="button" onClick={testTRPCEcho} disabled={loading}>
              Test Echo
            </button>
          </div>
          {trpcResponse && (
            <pre className="apiResponse">
              {trpcResponse}
            </pre>
          )}
        </div>
      </div>

      <div style={{ marginTop: '3rem', padding: '1rem', background: '#f0f0f0', borderRadius: '8px' }}>
        <h3>主な違い</h3>
        <ul style={{ lineHeight: '1.8' }}>
          <li><strong>REST API</strong>: 従来のHTTPエンドポイント形式、手動での型定義が必要</li>
          <li><strong>tRPC</strong>: 型安全なRPC、自動的な型推論、Zodによるバリデーション</li>
        </ul>
        <p style={{ marginTop: '1rem', fontSize: '0.9rem', color: '#666' }}>
          ※ このページは直接HTTPリクエストを送信しています。tRPCクライアントは使用していません。
        </p>
      </div>
    </div>
  );
}