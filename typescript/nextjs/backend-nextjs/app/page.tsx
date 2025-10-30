export default function Home() {
  return (
    <div style={{ padding: '2rem', fontFamily: 'monospace' }}>
      <h1>Next.js Backend API Server</h1>
      <p>This is a Next.js instance running as a dedicated API backend on port 3004</p>
      <h2>Available Endpoints:</h2>
      <ul>
        <li>GET /api/health</li>
        <li>GET /api/hello</li>
        <li>POST /api/echo</li>
      </ul>
    </div>
  );
}