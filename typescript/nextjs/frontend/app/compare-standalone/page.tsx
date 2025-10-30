'use client';

import { useState } from 'react';
import { trpcHono, trpcFastify } from '../../lib/trpc';

export default function CompareStandalonePage() {
  const [restApiResponse, setRestApiResponse] = useState<string>('');
  const [trpcResponse, setTrpcResponse] = useState<string>('');
  const [trpcFastifyResponse, setTrpcFastifyResponse] = useState<string>('');
  const [nextjsResponse, setNextjsResponse] = useState<string>('');
  const [nextjsBackendResponse, setNextjsBackendResponse] = useState<string>('');
  const [frontendAsBackendResponse, setFrontendAsBackendResponse] = useState<string>('');
  const [loading, setLoading] = useState(false);

  // REST API calls to Express backend
  const fetchFromRestAPI = async () => {
    setLoading(true);
    try {
      const response = await fetch('http://localhost:3001/api/hello');
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
      const response = await fetch('http://localhost:3001/api/echo', {
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

  // tRPC + Hono calls using tRPC client
  const fetchFromTRPC = async () => {
    setLoading(true);
    try {
      const result = await trpcHono.hello.query();
      setTrpcResponse(JSON.stringify(result, null, 2));
    } catch (error) {
      setTrpcResponse(`Error: ${error}`);
    } finally {
      setLoading(false);
    }
  };

  const testTRPCEcho = async () => {
    setLoading(true);
    try {
      const result = await trpcHono.echo.mutate({
        message: 'Hello from Frontend via tRPC Hono Client!',
      });
      setTrpcResponse(JSON.stringify(result, null, 2));
    } catch (error) {
      setTrpcResponse(`Error: ${error}`);
    } finally {
      setLoading(false);
    }
  };

  // tRPC + Fastify calls using tRPC client
  const fetchFromTRPCFastify = async () => {
    setLoading(true);
    try {
      const result = await trpcFastify.hello.query();
      setTrpcFastifyResponse(JSON.stringify(result, null, 2));
    } catch (error) {
      setTrpcFastifyResponse(`Error: ${error}`);
    } finally {
      setLoading(false);
    }
  };

  const testTRPCFastifyEcho = async () => {
    setLoading(true);
    try {
      const result = await trpcFastify.echo.mutate({
        message: 'Hello from Frontend via tRPC Fastify Client!',
      });
      setTrpcFastifyResponse(JSON.stringify(result, null, 2));
    } catch (error) {
      setTrpcFastifyResponse(`Error: ${error}`);
    } finally {
      setLoading(false);
    }
  };

  // Next.js API Routes calls
  const fetchFromNextjsAPI = async () => {
    setLoading(true);
    try {
      const response = await fetch('/api/nextjs/hello');
      const data = await response.json();
      setNextjsResponse(JSON.stringify(data, null, 2));
    } catch (error) {
      setNextjsResponse(`Error: ${error}`);
    } finally {
      setLoading(false);
    }
  };

  const testNextjsEcho = async () => {
    setLoading(true);
    try {
      const response = await fetch('/api/nextjs/echo', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({ message: 'Hello from Frontend via Next.js API Routes!' }),
      });
      const data = await response.json();
      setNextjsResponse(JSON.stringify(data, null, 2));
    } catch (error) {
      setNextjsResponse(`Error: ${error}`);
    } finally {
      setLoading(false);
    }
  };

  // Next.js Backend (Separate Process) calls
  const fetchFromNextjsBackend = async () => {
    setLoading(true);
    try {
      const response = await fetch('http://localhost:3004/api/hello');
      const data = await response.json();
      setNextjsBackendResponse(JSON.stringify(data, null, 2));
    } catch (error) {
      setNextjsBackendResponse(`Error: ${error}`);
    } finally {
      setLoading(false);
    }
  };

  const testNextjsBackendEcho = async () => {
    setLoading(true);
    try {
      const response = await fetch('http://localhost:3004/api/echo', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({ message: 'Hello from Frontend via Next.js Backend!' }),
      });
      const data = await response.json();
      setNextjsBackendResponse(JSON.stringify(data, null, 2));
    } catch (error) {
      setNextjsBackendResponse(`Error: ${error}`);
    } finally {
      setLoading(false);
    }
  };

  // Frontend as Backend (Same App, Different Process) calls
  const fetchFromFrontendAsBackend = async () => {
    setLoading(true);
    try {
      const response = await fetch('http://localhost:3005/api/nextjs/hello');
      const data = await response.json();
      setFrontendAsBackendResponse(JSON.stringify(data, null, 2));
    } catch (error) {
      setFrontendAsBackendResponse(`Error: ${error}`);
    } finally {
      setLoading(false);
    }
  };

  const testFrontendAsBackendEcho = async () => {
    setLoading(true);
    try {
      const response = await fetch('http://localhost:3005/api/nextjs/echo', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({ message: 'Hello from Frontend via Same App Backend!' }),
      });
      const data = await response.json();
      setFrontendAsBackendResponse(JSON.stringify(data, null, 2));
    } catch (error) {
      setFrontendAsBackendResponse(`Error: ${error}`);
    } finally {
      setLoading(false);
    }
  };

  return (
    <div className="container">
      <h1 className="title">バックエンド実装パターン比較</h1>
      <p className="description">
        6つの異なるバックエンド実装の比較
      </p>
      
      <div style={{ display: 'grid', gridTemplateColumns: 'repeat(3, 1fr)', gap: '1.5rem', marginTop: '2rem' }}>
        <div>
          <h2 style={{ fontSize: '1.25rem' }}>Next.js API Routes (同一プロセス)</h2>
          <p style={{ color: '#666', fontSize: '0.9rem', marginBottom: '1rem' }}>
            フロントエンドと同じプロセス・ポート3002
          </p>
          <div>
            <button className="button" onClick={fetchFromNextjsAPI} disabled={loading} style={{ marginBottom: '0.5rem', width: '100%' }}>
              Fetch Hello
            </button>
            <button className="button" onClick={testNextjsEcho} disabled={loading} style={{ width: '100%' }}>
              Test Echo
            </button>
          </div>
          {nextjsResponse && (
            <pre className="apiResponse" style={{ fontSize: '0.8rem', marginTop: '1rem' }}>
              {nextjsResponse}
            </pre>
          )}
        </div>

        <div>
          <h2 style={{ fontSize: '1.25rem' }}>同一コード別プロセス</h2>
          <p style={{ color: '#666', fontSize: '0.9rem', marginBottom: '1rem' }}>
            frontendコードのまま別起動・ポート3005
          </p>
          <div>
            <button className="button" onClick={fetchFromFrontendAsBackend} disabled={loading} style={{ marginBottom: '0.5rem', width: '100%' }}>
              Fetch Hello
            </button>
            <button className="button" onClick={testFrontendAsBackendEcho} disabled={loading} style={{ width: '100%' }}>
              Test Echo
            </button>
          </div>
          {frontendAsBackendResponse && (
            <pre className="apiResponse" style={{ fontSize: '0.8rem', marginTop: '1rem' }}>
              {frontendAsBackendResponse}
            </pre>
          )}
        </div>

        <div>
          <h2 style={{ fontSize: '1.25rem' }}>Next.js Backend (別プロセス)</h2>
          <p style={{ color: '#666', fontSize: '0.9rem', marginBottom: '1rem' }}>
            別Next.jsインスタンス・ポート3004
          </p>
          <div>
            <button className="button" onClick={fetchFromNextjsBackend} disabled={loading} style={{ marginBottom: '0.5rem', width: '100%' }}>
              Fetch Hello
            </button>
            <button className="button" onClick={testNextjsBackendEcho} disabled={loading} style={{ width: '100%' }}>
              Test Echo
            </button>
          </div>
          {nextjsBackendResponse && (
            <pre className="apiResponse" style={{ fontSize: '0.8rem', marginTop: '1rem' }}>
              {nextjsBackendResponse}
            </pre>
          )}
        </div>

        <div>
          <h2 style={{ fontSize: '1.25rem' }}>Express (REST API)</h2>
          <p style={{ color: '#666', fontSize: '0.9rem', marginBottom: '1rem' }}>
            別プロセス・ポート3001
          </p>
          <div>
            <button className="button" onClick={fetchFromRestAPI} disabled={loading} style={{ marginBottom: '0.5rem', width: '100%' }}>
              Fetch Hello
            </button>
            <button className="button" onClick={testRestEcho} disabled={loading} style={{ width: '100%' }}>
              Test Echo
            </button>
          </div>
          {restApiResponse && (
            <pre className="apiResponse" style={{ fontSize: '0.8rem', marginTop: '1rem' }}>
              {restApiResponse}
            </pre>
          )}
        </div>

        <div>
          <h2 style={{ fontSize: '1.25rem' }}>tRPC + Hono</h2>
          <p style={{ color: '#666', fontSize: '0.9rem', marginBottom: '1rem' }}>
            別プロセス・ポート3003・tRPCクライアント使用
          </p>
          <div>
            <button className="button" onClick={fetchFromTRPC} disabled={loading} style={{ marginBottom: '0.5rem', width: '100%' }}>
              Fetch Hello
            </button>
            <button className="button" onClick={testTRPCEcho} disabled={loading} style={{ width: '100%' }}>
              Test Echo
            </button>
          </div>
          {trpcResponse && (
            <pre className="apiResponse" style={{ fontSize: '0.8rem', marginTop: '1rem' }}>
              {trpcResponse}
            </pre>
          )}
        </div>

        <div>
          <h2 style={{ fontSize: '1.25rem' }}>tRPC + Fastify</h2>
          <p style={{ color: '#666', fontSize: '0.9rem', marginBottom: '1rem' }}>
            別プロセス・ポート3006・tRPCクライアント使用
          </p>
          <div>
            <button className="button" onClick={fetchFromTRPCFastify} disabled={loading} style={{ marginBottom: '0.5rem', width: '100%' }}>
              Fetch Hello
            </button>
            <button className="button" onClick={testTRPCFastifyEcho} disabled={loading} style={{ width: '100%' }}>
              Test Echo
            </button>
          </div>
          {trpcFastifyResponse && (
            <pre className="apiResponse" style={{ fontSize: '0.8rem', marginTop: '1rem' }}>
              {trpcFastifyResponse}
            </pre>
          )}
        </div>
      </div>

      <div style={{ marginTop: '3rem', padding: '1.5rem', background: '#f0f0f0', borderRadius: '8px' }}>
        <h3>アーキテクチャ比較</h3>
        <table style={{ width: '100%', borderCollapse: 'collapse', marginTop: '1rem' }}>
          <thead>
            <tr style={{ borderBottom: '2px solid #ccc' }}>
              <th style={{ padding: '0.5rem', textAlign: 'left' }}>特徴</th>
              <th style={{ padding: '0.5rem', textAlign: 'left' }}>Next.js<br />(同一プロセス)</th>
              <th style={{ padding: '0.5rem', textAlign: 'left' }}>同一コード<br />(別プロセス)</th>
              <th style={{ padding: '0.5rem', textAlign: 'left' }}>Next.js<br />(専用Backend)</th>
              <th style={{ padding: '0.5rem', textAlign: 'left' }}>Express</th>
              <th style={{ padding: '0.5rem', textAlign: 'left' }}>tRPC + Hono</th>
              <th style={{ padding: '0.5rem', textAlign: 'left' }}>tRPC + Fastify</th>
            </tr>
          </thead>
          <tbody>
            <tr style={{ borderBottom: '1px solid #ddd' }}>
              <td style={{ padding: '0.5rem' }}>デプロイ</td>
              <td style={{ padding: '0.5rem' }}>一体型</td>
              <td style={{ padding: '0.5rem' }}>分離可能</td>
              <td style={{ padding: '0.5rem' }}>分離可能</td>
              <td style={{ padding: '0.5rem' }}>分離可能</td>
              <td style={{ padding: '0.5rem' }}>分離可能</td>
              <td style={{ padding: '0.5rem' }}>分離可能</td>
            </tr>
            <tr style={{ borderBottom: '1px solid #ddd' }}>
              <td style={{ padding: '0.5rem' }}>コードベース</td>
              <td style={{ padding: '0.5rem' }}>共有</td>
              <td style={{ padding: '0.5rem' }}>共有</td>
              <td style={{ padding: '0.5rem' }}>独立</td>
              <td style={{ padding: '0.5rem' }}>独立</td>
              <td style={{ padding: '0.5rem' }}>独立</td>
              <td style={{ padding: '0.5rem' }}>独立</td>
            </tr>
            <tr style={{ borderBottom: '1px solid #ddd' }}>
              <td style={{ padding: '0.5rem' }}>UI含む</td>
              <td style={{ padding: '0.5rem' }}>Yes</td>
              <td style={{ padding: '0.5rem' }}>Yes</td>
              <td style={{ padding: '0.5rem' }}>最小限</td>
              <td style={{ padding: '0.5rem' }}>No</td>
              <td style={{ padding: '0.5rem' }}>No</td>
              <td style={{ padding: '0.5rem' }}>No</td>
            </tr>
            <tr style={{ borderBottom: '1px solid #ddd' }}>
              <td style={{ padding: '0.5rem' }}>スケーリング</td>
              <td style={{ padding: '0.5rem' }}>一体</td>
              <td style={{ padding: '0.5rem' }}>独立</td>
              <td style={{ padding: '0.5rem' }}>独立</td>
              <td style={{ padding: '0.5rem' }}>独立</td>
              <td style={{ padding: '0.5rem' }}>独立</td>
              <td style={{ padding: '0.5rem' }}>独立</td>
            </tr>
            <tr>
              <td style={{ padding: '0.5rem' }}>メンテナンス</td>
              <td style={{ padding: '0.5rem' }}>シンプル</td>
              <td style={{ padding: '0.5rem' }}>同一コード</td>
              <td style={{ padding: '0.5rem' }}>別管理</td>
              <td style={{ padding: '0.5rem' }}>別管理</td>
              <td style={{ padding: '0.5rem' }}>別管理</td>
              <td style={{ padding: '0.5rem' }}>別管理</td>
            </tr>
          </tbody>
        </table>
      </div>
    </div>
  );
}